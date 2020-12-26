#include "Game/AI/Action/actionWaterExplode.h"

namespace uking::action {

WaterExplode::WaterExplode(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaterExplode::~WaterExplode() = default;

bool WaterExplode::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaterExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaterExplode::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaterExplode::loadParams_() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mSpeed_s, "Speed");
}

void WaterExplode::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
