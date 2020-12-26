#include "Game/AI/Action/actionEmitElectricWaterBall.h"

namespace uking::action {

EmitElectricWaterBall::EmitElectricWaterBall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EmitElectricWaterBall::~EmitElectricWaterBall() = default;

bool EmitElectricWaterBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EmitElectricWaterBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EmitElectricWaterBall::leave_() {
    ksys::act::ai::Action::leave_();
}

void EmitElectricWaterBall::loadParams_() {
    getStaticParam(&mActorName_s, "ActorName");
}

void EmitElectricWaterBall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
