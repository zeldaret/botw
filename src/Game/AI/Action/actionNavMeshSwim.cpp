#include "Game/AI/Action/actionNavMeshSwim.h"

namespace uking::action {

NavMeshSwim::NavMeshSwim(const InitArg& arg) : NavMeshAction(arg) {}

NavMeshSwim::~NavMeshSwim() = default;

bool NavMeshSwim::init_(sead::Heap* heap) {
    return NavMeshAction::init_(heap);
}

void NavMeshSwim::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshAction::enter_(params);
}

void NavMeshSwim::leave_() {
    NavMeshAction::leave_();
}

void NavMeshSwim::loadParams_() {
    NavMeshAction::loadParams_();
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mASName_s, "ASName");
}

void NavMeshSwim::calc_() {
    NavMeshAction::calc_();
}

}  // namespace uking::action
