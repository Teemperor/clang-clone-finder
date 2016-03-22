#ifndef STANDALONE_FAKECCLISTENER_H
#define STANDALONE_FAKECCLISTENER_H

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>
#include "InterProcessArgs.h"

class FakeCCListener {

    boost::interprocess::shared_memory_object shm;
    boost::interprocess::mapped_region region;
    InterProcessArgs* data;

public:
    FakeCCListener();

    virtual ~FakeCCListener();

    void run();
};


#endif //STANDALONE_FAKECCLISTENER_H
