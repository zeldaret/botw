#include "Game/AI/Action/actionDragonChemicalBall.h"

namespace uking::action {

DragonChemicalBall::DragonChemicalBall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DragonChemicalBall::~DragonChemicalBall() = default;

bool DragonChemicalBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DragonChemicalBall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DragonChemicalBall::leave_() {
    ksys::act::ai::Action::leave_();
}

void DragonChemicalBall::loadParams_() {
    getStaticParam(&mLife_s, "Life");
    getStaticParam(&mHitScale_s, "HitScale");
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mHomingPower_s, "HomingPower");
    getStaticParam(&mHomingDistance_s, "HomingDistance");
    getStaticParam(&mHomingTime_s, "HomingTime");
}

void DragonChemicalBall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
