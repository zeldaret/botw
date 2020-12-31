#include "Game/AI/AI/aiDungeonResetPosTag.h"

namespace uking::ai {

DungeonResetPosTag::DungeonResetPosTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonResetPosTag::~DungeonResetPosTag() = default;

bool DungeonResetPosTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonResetPosTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DungeonResetPosTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonResetPosTag::loadParams_() {}

}  // namespace uking::ai
