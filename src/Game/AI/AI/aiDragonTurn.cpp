#include "Game/AI/AI/aiDragonTurn.h"

namespace uking::ai {

DragonTurn::DragonTurn(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DragonTurn::~DragonTurn() = default;

bool DragonTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DragonTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DragonTurn::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DragonTurn::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mAvoidStartDistance_s, "AvoidStartDistance");
    getDynamicParam(&mTargetVec_d, "TargetVec");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
