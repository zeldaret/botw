#include "Game/AI/Action/actionReboundHit.h"

namespace uking::action {

ReboundHit::ReboundHit(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void ReboundHit::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ReboundHit::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mGravityRate_s, "GravityRate");
}

}  // namespace uking::action
