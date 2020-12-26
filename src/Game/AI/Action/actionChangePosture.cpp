#include "Game/AI/Action/actionChangePosture.h"

namespace uking::action {

ChangePosture::ChangePosture(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangePosture::~ChangePosture() = default;

bool ChangePosture::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangePosture::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChangePosture::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChangePosture::loadParams_() {
    getDynamicParam(&mPosture_d, "Posture");
}

void ChangePosture::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
