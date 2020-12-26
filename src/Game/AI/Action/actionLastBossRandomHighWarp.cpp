#include "Game/AI/Action/actionLastBossRandomHighWarp.h"

namespace uking::action {

LastBossRandomHighWarp::LastBossRandomHighWarp(const InitArg& arg) : LastBossNormalWarp(arg) {}

LastBossRandomHighWarp::~LastBossRandomHighWarp() = default;

bool LastBossRandomHighWarp::init_(sead::Heap* heap) {
    return LastBossNormalWarp::init_(heap);
}

void LastBossRandomHighWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossNormalWarp::enter_(params);
}

void LastBossRandomHighWarp::leave_() {
    LastBossNormalWarp::leave_();
}

void LastBossRandomHighWarp::loadParams_() {
    LastBossNormalWarp::loadParams_();
    getStaticParam(&mHighPosWarpRate_s, "HighPosWarpRate");
    getStaticParam(&mRandomRate_s, "RandomRate");
    getStaticParam(&mHighOffsetY_s, "HighOffsetY");
    getStaticParam(&mLifeCondition_s, "LifeCondition");
}

void LastBossRandomHighWarp::calc_() {
    LastBossNormalWarp::calc_();
}

}  // namespace uking::action
