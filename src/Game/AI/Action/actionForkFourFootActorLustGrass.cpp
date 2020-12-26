#include "Game/AI/Action/actionForkFourFootActorLustGrass.h"

namespace uking::action {

ForkFourFootActorLustGrass::ForkFourFootActorLustGrass(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkFourFootActorLustGrass::~ForkFourFootActorLustGrass() = default;

bool ForkFourFootActorLustGrass::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkFourFootActorLustGrass::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkFourFootActorLustGrass::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkFourFootActorLustGrass::loadParams_() {
    getStaticParam(&mMaxRadius_s, "MaxRadius");
    getStaticParam(&mMinRadius_s, "MinRadius");
    getStaticParam(&mNode1Name_s, "Node1Name");
    getStaticParam(&mNode2Name_s, "Node2Name");
    getStaticParam(&mNode3Name_s, "Node3Name");
    getStaticParam(&mNode4Name_s, "Node4Name");
    getStaticParam(&mWorldOffset_s, "WorldOffset");
    getStaticParam(&mRadSpd_s, "RadSpd");
    getAITreeVariable(&mGanonBeastGrudgeMarkMgr_a, "GanonBeastGrudgeMarkMgr");
}

void ForkFourFootActorLustGrass::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
