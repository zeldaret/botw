#include "Game/AI/Action/actionGanonBarrierOn.h"

namespace uking::action {

GanonBarrierOn::GanonBarrierOn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonBarrierOn::~GanonBarrierOn() = default;

bool GanonBarrierOn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonBarrierOn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonBarrierOn::leave_() {
    ksys::act::ai::Action::leave_();
}

void GanonBarrierOn::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

void GanonBarrierOn::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
