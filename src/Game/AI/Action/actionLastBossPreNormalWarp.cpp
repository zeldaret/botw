#include "Game/AI/Action/actionLastBossPreNormalWarp.h"

namespace uking::action {

LastBossPreNormalWarp::LastBossPreNormalWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LastBossPreNormalWarp::~LastBossPreNormalWarp() = default;

bool LastBossPreNormalWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LastBossPreNormalWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LastBossPreNormalWarp::leave_() {
    ksys::act::ai::Action::leave_();
}

void LastBossPreNormalWarp::loadParams_() {
    getStaticParam(&mPreWarpWaitTime_s, "PreWarpWaitTime");
    getStaticParam(&mPosReduce_s, "PosReduce");
    getStaticParam(&mIsDeleteEffect_s, "IsDeleteEffect");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mIsPartsWarpEffectSync_d, "IsPartsWarpEffectSync");
}

void LastBossPreNormalWarp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
