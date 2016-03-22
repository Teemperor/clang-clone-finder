

#include "../clone-finder/InterProcessArgs.h"

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>

using namespace boost::interprocess;

int main(int argc, char** argv) {

    /*Erase previous shared memory and schedule erasure on exit
    struct shm_remove {
        shm_remove() { shared_memory_object::remove(interProcessName.c_str()); }
        ~shm_remove(){ shared_memory_object::remove(interProcessName.c_str()); }
    } remover;
    */

    //Create a shared memory object.
    shared_memory_object shm (open_only, interProcessName.c_str(), read_write);
    try {
        //Set size
        shm.truncate(sizeof(InterProcessArgs));

        //Map the whole shared memory in this process
        mapped_region region(shm, read_write);

        //Get the address of the mapped region
        void* addr = region.get_address();

        //Obtain a pointer to the shared structure
        InterProcessArgs* data = static_cast<InterProcessArgs*>(addr);

        scoped_lock<interprocess_mutex> lock(data->mutex);
        if(data->message_in) {
            data->cond_full.wait(lock);
        }

        std::stringstream args;

        for (int arg = 1; arg < argc; ++arg) {
            args << " " << argv[arg];
        }

        if (std::snprintf(data->items, data->LineSize, "%s", args.str().c_str()) > data->LineSize) {
            std::cerr << "not enough shared memory to write arg" << std::endl;
            return 1;
        }


        //Notify to the other process that there is a message
        data->cond_empty.notify_one();

        //Mark message buffer as full
        data->message_in = true;
    } catch(interprocess_exception &ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    }

    return 0;
}