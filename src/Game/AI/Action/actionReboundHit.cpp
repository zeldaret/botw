#include "Game/AI/Action/actionReboundHit.h"

namespace uking::action {

ReboundHit::ReboundHit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ReboundHit::~ReboundHit() = default;

bool ReboundHit::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ReboundHit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ReboundHit::leave_() {
    ksys::act::ai::Action::leave_();
}

void ReboundHit::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mGravityRate_s, "GravityRate");
}

void ReboundHit::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
