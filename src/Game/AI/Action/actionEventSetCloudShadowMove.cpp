#include "Game/AI/Action/actionEventSetCloudShadowMove.h"

namespace uking::action {

EventSetCloudShadowMove::EventSetCloudShadowMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetCloudShadowMove::~EventSetCloudShadowMove() = default;

bool EventSetCloudShadowMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetCloudShadowMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetCloudShadowMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetCloudShadowMove::loadParams_() {
    getDynamicParam(&msetSpeed_x_d, "setSpeed_x");
    getDynamicParam(&msetSpeed_y_d, "setSpeed_y");
}

void EventSetCloudShadowMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
