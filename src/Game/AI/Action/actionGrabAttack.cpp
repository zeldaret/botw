#include "Game/AI/Action/actionGrabAttack.h"

namespace uking::action {

GrabAttack::GrabAttack(const InitArg& arg) : Grab(arg) {}

GrabAttack::~GrabAttack() = default;

void GrabAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    Grab::enter_(params);
}

void GrabAttack::leave_() {
    Grab::leave_();
}

void GrabAttack::loadParams_() {
    Grab::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAtRigidBodyName_s, "AtRigidBodyName");
}

void GrabAttack::calc_() {
    Grab::calc_();
}

}  // namespace uking::action
