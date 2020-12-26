#include "Game/AI/Action/actionGuardianAimBeamWithAS.h"

namespace uking::action {

GuardianAimBeamWithAS::GuardianAimBeamWithAS(const InitArg& arg) : GuardianAimBeam(arg) {}

GuardianAimBeamWithAS::~GuardianAimBeamWithAS() = default;

bool GuardianAimBeamWithAS::init_(sead::Heap* heap) {
    return GuardianAimBeam::init_(heap);
}

void GuardianAimBeamWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianAimBeam::enter_(params);
}

void GuardianAimBeamWithAS::leave_() {
    GuardianAimBeam::leave_();
}

void GuardianAimBeamWithAS::loadParams_() {
    GuardianAimBeam::loadParams_();
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mASName_s, "ASName");
}

void GuardianAimBeamWithAS::calc_() {
    GuardianAimBeam::calc_();
}

}  // namespace uking::action
