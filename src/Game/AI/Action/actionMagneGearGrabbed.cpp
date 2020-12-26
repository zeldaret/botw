#include "Game/AI/Action/actionMagneGearGrabbed.h"

namespace uking::action {

MagneGearGrabbed::MagneGearGrabbed(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MagneGearGrabbed::~MagneGearGrabbed() = default;

bool MagneGearGrabbed::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MagneGearGrabbed::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MagneGearGrabbed::leave_() {
    ksys::act::ai::Action::leave_();
}

void MagneGearGrabbed::loadParams_() {
    getStaticParam(&mConnectDistance_s, "ConnectDistance");
}

void MagneGearGrabbed::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
