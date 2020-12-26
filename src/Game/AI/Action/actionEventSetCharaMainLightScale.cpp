#include "Game/AI/Action/actionEventSetCharaMainLightScale.h"

namespace uking::action {

EventSetCharaMainLightScale::EventSetCharaMainLightScale(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetCharaMainLightScale::~EventSetCharaMainLightScale() = default;

bool EventSetCharaMainLightScale::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetCharaMainLightScale::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetCharaMainLightScale::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetCharaMainLightScale::loadParams_() {
    getDynamicParam(&mRscale_d, "Rscale");
    getDynamicParam(&mGscale_d, "Gscale");
    getDynamicParam(&mBscale_d, "Bscale");
}

void EventSetCharaMainLightScale::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
