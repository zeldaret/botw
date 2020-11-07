#pragma once

#include <heap/seadDisposer.h>

namespace ksys {

namespace res {
class GParamList;
}  // namespace res

namespace act {

// FIXME: incomplete
class ActorParamMgr {
    SEAD_SINGLETON_DISPOSER(ActorParamMgr)
public:
    void init(sead::Heap* heap, sead::Heap* debug_heap);

    res::GParamList* getDummyGParamList() const;
};

}  // namespace act

}  // namespace ksys
