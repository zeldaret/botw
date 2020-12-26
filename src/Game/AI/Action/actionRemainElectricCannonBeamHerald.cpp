#include "Game/AI/Action/actionRemainElectricCannonBeamHerald.h"

namespace uking::action {

RemainElectricCannonBeamHerald::RemainElectricCannonBeamHerald(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RemainElectricCannonBeamHerald::~RemainElectricCannonBeamHerald() = default;

bool RemainElectricCannonBeamHerald::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RemainElectricCannonBeamHerald::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RemainElectricCannonBeamHerald::leave_() {
    ksys::act::ai::Action::leave_();
}

void RemainElectricCannonBeamHerald::loadParams_() {
    getStaticParam(&mHeraldTime_s, "HeraldTime");
    getDynamicParam(&mWillBeProtected_d, "WillBeProtected");
}

void RemainElectricCannonBeamHerald::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
