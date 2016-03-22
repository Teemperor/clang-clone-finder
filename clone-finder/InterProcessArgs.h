#ifndef STANDALONE_INTERPROCESSARGS_H_H
#define STANDALONE_INTERPROCESSARGS_H_H

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

struct InterProcessArgs
{
    enum { LineSize = 4096 };

    InterProcessArgs()
            :  message_in(false)
    {}

    //Mutex to protect access to the queue
    boost::interprocess::interprocess_mutex mutex;

    //Condition to wait when the queue is empty
    boost::interprocess::interprocess_condition cond_empty;

    //Condition to wait when the queue is full
    boost::interprocess::interprocess_condition cond_full;

    //Items to fill
    char   items[LineSize];

    //Is there any message
    bool message_in;
};

const std::string interProcessName = "clang-clone-finder-arg";

#endif //STANDALONE_INTERPROCESSARGS_H_H
