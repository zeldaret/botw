#pragma once

#include <basis/seadTypes.h>

namespace sead {
class Heap;
}

namespace ksys::util {
class TaskMgr;
class TaskQueue;
}  // namespace ksys::util

namespace ksys::act {

class BaseProcInitializer {
public:
    BaseProcInitializer();
    virtual ~BaseProcInitializer();

    BaseProcInitializer(const BaseProcInitializer&) = delete;
    auto operator=(const BaseProcInitializer&) = delete;

    u32 get8() const { return _8; }
    void set8(u32 value) { _8 = value; }

    bool isActorGenerationEnabled() const { return mActorGenerationEnabled; }
    void setActorGenerationEnabled(bool enabled) { mActorGenerationEnabled = enabled; }

private:
    u32 _8 = 0;
    void* _10 = nullptr;
    util::TaskMgr* mTaskMgr = nullptr;
    util::TaskQueue* mTaskQueue = nullptr;
    sead::Heap* mHeap = nullptr;
    bool mActorGenerationEnabled = true;
};

}  // namespace ksys::act
