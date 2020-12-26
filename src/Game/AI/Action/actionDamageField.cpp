#include "Game/AI/Action/actionDamageField.h"

namespace uking::action {

DamageField::DamageField(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DamageField::~DamageField() = default;

bool DamageField::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DamageField::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DamageField::leave_() {
    ksys::act::ai::Action::leave_();
}

void DamageField::loadParams_() {
    getStaticParam(&mFieldType_s, "FieldType");
    getStaticParam(&mRigidSetName_s, "RigidSetName");
    getStaticParam(&mIsChangeRigidWorldMode_s, "IsChangeRigidWorldMode");
    getStaticParam(&mIsUseCollisionInfo_s, "IsUseCollisionInfo");
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
    getStaticParam(&mCollisionInfoName_s, "CollisionInfoName");
}

void DamageField::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
