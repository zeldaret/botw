#include "Game/AI/Action/actionSetEnableWaterHit.h"

namespace uking::action {

SetEnableWaterHit::SetEnableWaterHit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetEnableWaterHit::~SetEnableWaterHit() = default;

bool SetEnableWaterHit::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetEnableWaterHit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetEnableWaterHit::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetEnableWaterHit::loadParams_() {
    getStaticParam(&mWaterHit_s, "WaterHit");
}

void SetEnableWaterHit::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
