#include "Game/AI/AI/aiDungeonRemainsFire.h"

namespace uking::ai {

DungeonRemainsFire::DungeonRemainsFire(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonRemainsFire::~DungeonRemainsFire() = default;

bool DungeonRemainsFire::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRemainsFire::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DungeonRemainsFire::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRemainsFire::loadParams_() {
    getStaticParam(&mRailName_s, "RailName");
}

}  // namespace uking::ai
