#include "Game/Actor/Action/actionNavMeshSwim.h"

namespace uking::action {

NavMeshSwim::NavMeshSwim(const InitArg& arg) : NavMeshMoveBase(arg) {}

NavMeshSwim::~NavMeshSwim() = default;

bool NavMeshSwim::init_(sead::Heap* heap) {
    return NavMeshMoveBase::init_(heap);
}

void NavMeshSwim::enter_(ksys::act::ai::InlineParamPack* params) {
    NavMeshMoveBase::enter_(params);
}

void NavMeshSwim::leave_() {
    NavMeshMoveBase::leave_();
}

void NavMeshSwim::loadParams_() {
    NavMeshMoveBase::loadParams_();
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mASName_s, "ASName");
}

void NavMeshSwim::calc_() {
    NavMeshMoveBase::calc_();
}

}  // namespace uking::action
