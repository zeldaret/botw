#include "Game/AI/Action/actionSiteBossBowMoveForArrowRain.h"

namespace uking::action {

SiteBossBowMoveForArrowRain::SiteBossBowMoveForArrowRain(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossBowMoveForArrowRain::~SiteBossBowMoveForArrowRain() = default;

bool SiteBossBowMoveForArrowRain::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossBowMoveForArrowRain::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossBowMoveForArrowRain::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossBowMoveForArrowRain::loadParams_() {
    getStaticParam(&mFirstMoveSpeed_s, "FirstMoveSpeed");
    getStaticParam(&mFirstAccelFrame_s, "FirstAccelFrame");
    getStaticParam(&mSecondMoveSpeed_s, "SecondMoveSpeed");
    getStaticParam(&mSecondAccelFrame_s, "SecondAccelFrame");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mMoveTarget_s, "MoveTarget");
}

void SiteBossBowMoveForArrowRain::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
