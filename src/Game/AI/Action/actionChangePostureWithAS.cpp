#include "Game/AI/Action/actionChangePostureWithAS.h"

namespace uking::action {

ChangePostureWithAS::ChangePostureWithAS(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangePostureWithAS::~ChangePostureWithAS() = default;

bool ChangePostureWithAS::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangePostureWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChangePostureWithAS::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChangePostureWithAS::loadParams_() {
    getDynamicParam(&mPosture_d, "Posture");
}

void ChangePostureWithAS::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
