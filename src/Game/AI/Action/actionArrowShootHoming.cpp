#include "Game/AI/Action/actionArrowShootHoming.h"

namespace uking::action {

ArrowShootHoming::ArrowShootHoming(const InitArg& arg) : ArrowShootMove(arg) {}

ArrowShootHoming::~ArrowShootHoming() = default;

void ArrowShootHoming::enter_(ksys::act::ai::InlineParamPack* params) {
    ArrowShootMove::enter_(params);
}

void ArrowShootHoming::loadParams_() {
    ArrowShootMove::loadParams_();
    getStaticParam(&mSubAngMax_s, "SubAngMax");
    getStaticParam(&mHomingRate_s, "HomingRate");
    getStaticParam(&mNearDist_s, "NearDist");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getDynamicParam(&mHomingTargetPos_d, "HomingTargetPos");
}

void ArrowShootHoming::calc_() {
    ArrowShootMove::calc_();
}

}  // namespace uking::action
