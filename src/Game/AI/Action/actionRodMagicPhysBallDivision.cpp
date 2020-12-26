#include "Game/AI/Action/actionRodMagicPhysBallDivision.h"

namespace uking::action {

RodMagicPhysBallDivision::RodMagicPhysBallDivision(const InitArg& arg) : RodMagicPhysBall(arg) {}

RodMagicPhysBallDivision::~RodMagicPhysBallDivision() = default;

bool RodMagicPhysBallDivision::init_(sead::Heap* heap) {
    return RodMagicPhysBall::init_(heap);
}

void RodMagicPhysBallDivision::enter_(ksys::act::ai::InlineParamPack* params) {
    RodMagicPhysBall::enter_(params);
}

void RodMagicPhysBallDivision::leave_() {
    RodMagicPhysBall::leave_();
}

void RodMagicPhysBallDivision::loadParams_() {
    RodMagicPhysBall::loadParams_();
    getStaticParam(&mDivNum_s, "DivNum");
    getStaticParam(&mDivDist_s, "DivDist");
    getStaticParam(&mDivAngle_s, "DivAngle");
    getStaticParam(&mChildName_s, "ChildName");
}

void RodMagicPhysBallDivision::calc_() {
    RodMagicPhysBall::calc_();
}

}  // namespace uking::action
