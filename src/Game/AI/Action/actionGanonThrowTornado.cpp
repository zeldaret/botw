#include "Game/AI/Action/actionGanonThrowTornado.h"

namespace uking::action {

GanonThrowTornado::GanonThrowTornado(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonThrowTornado::~GanonThrowTornado() = default;

bool GanonThrowTornado::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonThrowTornado::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonThrowTornado::leave_() {
    ksys::act::ai::Action::leave_();
}

void GanonThrowTornado::loadParams_() {
    getStaticParam(&mInitVelocity_s, "InitVelocity");
    getStaticParam(&mCreateHeight_s, "CreateHeight");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mAppearOffset_s, "AppearOffset");
    getDynamicParam(&mThrowPartsName_d, "ThrowPartsName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void GanonThrowTornado::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
