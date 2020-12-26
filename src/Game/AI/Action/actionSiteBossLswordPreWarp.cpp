#include "Game/AI/Action/actionSiteBossLswordPreWarp.h"

namespace uking::action {

SiteBossLswordPreWarp::SiteBossLswordPreWarp(const InitArg& arg) : LastBossPreNormalWarp(arg) {}

SiteBossLswordPreWarp::~SiteBossLswordPreWarp() = default;

bool SiteBossLswordPreWarp::init_(sead::Heap* heap) {
    return LastBossPreNormalWarp::init_(heap);
}

void SiteBossLswordPreWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    LastBossPreNormalWarp::enter_(params);
}

void SiteBossLswordPreWarp::leave_() {
    LastBossPreNormalWarp::leave_();
}

void SiteBossLswordPreWarp::loadParams_() {
    LastBossPreNormalWarp::loadParams_();
    getStaticParam(&mSleepPartsName_s, "SleepPartsName");
}

void SiteBossLswordPreWarp::calc_() {
    LastBossPreNormalWarp::calc_();
}

}  // namespace uking::action
