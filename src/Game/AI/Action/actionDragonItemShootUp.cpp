#include "Game/AI/Action/actionDragonItemShootUp.h"

namespace uking::action {

DragonItemShootUp::DragonItemShootUp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DragonItemShootUp::~DragonItemShootUp() = default;

bool DragonItemShootUp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DragonItemShootUp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DragonItemShootUp::leave_() {
    ksys::act::ai::Action::leave_();
}

void DragonItemShootUp::loadParams_() {
    getStaticParam(&mFlyAwaySpeed_s, "FlyAwaySpeed");
    getStaticParam(&mContactSpeedDownXZ_s, "ContactSpeedDownXZ");
    getStaticParam(&mContactSpeedDownY_s, "ContactSpeedDownY");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void DragonItemShootUp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
