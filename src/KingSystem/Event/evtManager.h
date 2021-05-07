#pragma once

#include <heap/seadDisposer.h>

namespace ksys::act {
class Actor;
}

namespace ksys::evt {

class Event;
class Metadata;

// TODO
class Manager {
    SEAD_SINGLETON_DISPOSER(Manager)
    Manager();
    virtual ~Manager();

public:
    void init(sead::Heap* heap);

    Event* getActiveEvent() const;
    bool hasActiveEvent() const;

    bool callEvent(const Metadata& metadata, act::Actor* actor = nullptr, void* x = nullptr);

    sead::Heap* mEventHeap;  // 0x1d180
};

}  // namespace ksys::evt
