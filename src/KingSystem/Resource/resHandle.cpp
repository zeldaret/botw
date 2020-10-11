#include "KingSystem/Resource/resHandle.h"
#include <container/seadBuffer.h>
#include <prim/seadSafeString.h>
#include <time/seadTickTime.h>
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resSystem.h"

namespace ksys::res {

namespace {
struct UnusedVariables {
    sead::TickTime tick_time;
    void* _8 = nullptr;
    f32 _10 = 0.5;
    f32 _14 = 1.0;
    f32 _18 = 0.5;
    f32 _1c = 1.0;
};
}  // namespace

UnusedVariables sVariables;
const sead::SafeString sStatusStrings_[0x11] = {
    "            ",    // 0x0
    "[Unknown]   ",    // 0x1
    "[No File]   ",    // 0x2
    "[Request OK]",    // 0x3
    "[Already]   ",    // 0x4
    "[FromCache] ",    // 0x5
    "[No Memory] ",    // 0x6
    "[No Execute]",    // 0x7
    "[Size Zero] ",    // 0x8
    "[Compose NG]",    // 0x9
    "[AllocSizeNG]",   // 0xa
    "[Edited]    ",    // 0xb
    "[HeapSizeNG]",    // 0xc
    "[FileDeviceNG]",  // 0xd
    "[Load OK]",       // 0xe
    "[Yet]",           // 0xf
    "[Canceled]",      // 0x10
};
const sead::Buffer<const sead::SafeString> sStatusStrings{0x11, sStatusStrings_};

Handle::Handle() = default;

Handle::~Handle() {
    unload();
}

void Handle::unload() {
    if (!mFlags.isOn(Flag::_2))
        return;

    mFlags.reset(Flag::_7);
    mFlags.set(Flag::_4);

    if (mTaskHandle.hasTask()) {
        mTaskHandle.removeTaskFromQueue();
        if (!mUnit) {
            stubbedLogFunction();
            mStatus = Status::_14;
            return;
        }
    }

    if (!mUnit)
        return;

    if (ResourceMgrTask::instance())
        ResourceMgrTask::instance()->requestUnload(this);
}

}  // namespace ksys::res
