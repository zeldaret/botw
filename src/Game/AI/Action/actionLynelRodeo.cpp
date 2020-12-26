#include "Game/AI/Action/actionLynelRodeo.h"

namespace uking::action {

LynelRodeo::LynelRodeo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LynelRodeo::~LynelRodeo() = default;

bool LynelRodeo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LynelRodeo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LynelRodeo::leave_() {
    ksys::act::ai::Action::leave_();
}

void LynelRodeo::loadParams_() {
    getStaticParam(&mForwardSpeed_s, "ForwardSpeed");
    getStaticParam(&mSideSpeed_s, "SideSpeed");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mTurnCheckAngleStep_s, "TurnCheckAngleStep");
}

void LynelRodeo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
