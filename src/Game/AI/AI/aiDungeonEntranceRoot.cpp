#include "Game/AI/AI/aiDungeonEntranceRoot.h"

namespace uking::ai {

DungeonEntranceRoot::DungeonEntranceRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonEntranceRoot::~DungeonEntranceRoot() = default;

bool DungeonEntranceRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonEntranceRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DungeonEntranceRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonEntranceRoot::loadParams_() {
    getStaticParam(&mIsCheckClear_s, "IsCheckClear");
}

}  // namespace uking::ai
