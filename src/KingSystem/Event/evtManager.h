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

    sead::Heap* getEventHeap() const { return mEventHeap; }

    bool callEvent(const Metadata& metadata, act::Actor* actor = nullptr, void* x = nullptr);

private:
    u8 pad_20[0x1d178 - 0x20];
    sead::Heap* mEventHeap;
};

}  // namespace ksys::evt
