#include "Game/AI/Action/actionPhysBodyPartLod.h"

namespace uking::action {

PhysBodyPartLod::PhysBodyPartLod(const InitArg& arg) : ksys::act::ai::Action(arg) {}

PhysBodyPartLod::~PhysBodyPartLod() = default;

bool PhysBodyPartLod::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void PhysBodyPartLod::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void PhysBodyPartLod::leave_() {
    ksys::act::ai::Action::leave_();
}

void PhysBodyPartLod::loadParams_() {
    getStaticParam(&mLodType_s, "LodType");
    getStaticParam(&mRemoveDistance_s, "RemoveDistance");
    getStaticParam(&mRemoveDistanceOffset_s, "RemoveDistanceOffset");
}

void PhysBodyPartLod::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
