#include "Game/AI/AI/aiDungeonRotateTag.h"

namespace uking::ai {

DungeonRotateTag::DungeonRotateTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool DungeonRotateTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRotateTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DungeonRotateTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRotateTag::loadParams_() {}

}  // namespace uking::ai
