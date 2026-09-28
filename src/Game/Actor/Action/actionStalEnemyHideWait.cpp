#include "Game/Actor/Action/actionStalEnemyHideWait.h"

namespace uking::action {

StalEnemyHideWait::StalEnemyHideWait(const InitArg& arg) : StopBase(arg) {}

StalEnemyHideWait::~StalEnemyHideWait() = default;

bool StalEnemyHideWait::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void StalEnemyHideWait::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void StalEnemyHideWait::leave_() {
    StopBase::leave_();
}

void StalEnemyHideWait::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void StalEnemyHideWait::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
