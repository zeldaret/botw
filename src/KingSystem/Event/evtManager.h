#pragma once

#include <heap/seadDisposer.h>

namespace ksys::evt {

class Event;

// TODO
class Manager {
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();
    virtual ~Manager();

public:
    void init(sead::Heap* heap);

    Event* getActiveEvent() const;
};

}  // namespace ksys::evt
