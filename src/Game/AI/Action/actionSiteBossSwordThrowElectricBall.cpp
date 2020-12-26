#include "Game/AI/Action/actionSiteBossSwordThrowElectricBall.h"

namespace uking::action {

SiteBossSwordThrowElectricBall::SiteBossSwordThrowElectricBall(const InitArg& arg)
    : SiteBossThrowParts(arg) {}

SiteBossSwordThrowElectricBall::~SiteBossSwordThrowElectricBall() = default;

bool SiteBossSwordThrowElectricBall::init_(sead::Heap* heap) {
    return SiteBossThrowParts::init_(heap);
}

void SiteBossSwordThrowElectricBall::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossThrowParts::enter_(params);
}

void SiteBossSwordThrowElectricBall::leave_() {
    SiteBossThrowParts::leave_();
}

void SiteBossSwordThrowElectricBall::loadParams_() {
    SiteBossThrowParts::loadParams_();
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mMoveOffset_s, "MoveOffset");
}

void SiteBossSwordThrowElectricBall::calc_() {
    SiteBossThrowParts::calc_();
}

}  // namespace uking::action
