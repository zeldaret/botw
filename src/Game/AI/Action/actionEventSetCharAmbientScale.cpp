#include "Game/AI/Action/actionEventSetCharAmbientScale.h"

namespace uking::action {

EventSetCharAmbientScale::EventSetCharAmbientScale(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetCharAmbientScale::~EventSetCharAmbientScale() = default;

bool EventSetCharAmbientScale::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetCharAmbientScale::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetCharAmbientScale::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetCharAmbientScale::loadParams_() {
    getDynamicParam(&mRscale_d, "Rscale");
    getDynamicParam(&mGscale_d, "Gscale");
    getDynamicParam(&mBscale_d, "Bscale");
}

void EventSetCharAmbientScale::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
