#include "FakeCCListener.h"

FakeCCListener::FakeCCListener()
{
    boost::interprocess::shared_memory_object::remove(interProcessName.c_str());

    shm = boost::interprocess::shared_memory_object(boost::interprocess::create_only, interProcessName.c_str(), boost::interprocess::read_write);
    shm.truncate(sizeof(InterProcessArgs));
    region = boost::interprocess::mapped_region(shm, boost::interprocess::read_write);


    //Get the address of the mapped region
    void* addr = region.get_address();

    //Construct the shared structure in memory
    data = new (addr) InterProcessArgs;

}

FakeCCListener::~FakeCCListener() {
    boost::interprocess::shared_memory_object::remove(interProcessName.c_str());
}

void FakeCCListener::run() {
    using namespace boost::interprocess;

    try{

        //Print messages until the other process marks the end
        bool end_loop = false;
        do {
            scoped_lock<interprocess_mutex> lock(data->mutex);
            if(!data->message_in) {
                data->cond_empty.wait(lock);
            }
            std::string itemsStr = data->items;
            if(itemsStr.find("-c") == std::string::npos) {
                end_loop = true;
            } else {
                //Print the message
                std::cout << "Data: " << data->items << std::endl;
                //Notify the other process that the buffer is empty
                data->message_in = false;
                data->cond_full.notify_one();
            }
        } while(!end_loop);
    }
    catch(interprocess_exception &ex){
        std::cerr << ex.what() << std::endl;
        abort();
    }
}