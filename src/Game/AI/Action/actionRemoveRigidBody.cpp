#include "Game/AI/Action/actionRemoveRigidBody.h"

namespace uking::action {

RemoveRigidBody::RemoveRigidBody(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RemoveRigidBody::~RemoveRigidBody() = default;

bool RemoveRigidBody::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemoveRigidBody::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemoveRigidBody::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemoveRigidBody::loadParams_() {
    getStaticParam(&mChangeLayer_s, "ChangeLayer");
}

void RemoveRigidBody::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
