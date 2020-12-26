#include "Game/AI/Action/actionEventSetCloudShadowPos.h"

namespace uking::action {

EventSetCloudShadowPos::EventSetCloudShadowPos(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetCloudShadowPos::~EventSetCloudShadowPos() = default;

bool EventSetCloudShadowPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetCloudShadowPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetCloudShadowPos::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetCloudShadowPos::loadParams_() {
    getDynamicParam(&msetPos_x_d, "setPos_x");
    getDynamicParam(&msetPos_y_d, "setPos_y");
}

void EventSetCloudShadowPos::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
