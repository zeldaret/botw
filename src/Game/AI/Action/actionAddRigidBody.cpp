#include "Game/AI/Action/actionAddRigidBody.h"

namespace uking::action {

AddRigidBody::AddRigidBody(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AddRigidBody::~AddRigidBody() = default;

bool AddRigidBody::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AddRigidBody::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AddRigidBody::leave_() {
    ksys::act::ai::Action::leave_();
}

void AddRigidBody::loadParams_() {
    getStaticParam(&mResetLayer_s, "ResetLayer");
}

void AddRigidBody::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
