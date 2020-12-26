#include "Game/AI/Action/actionSiteBossSwordWhirlSlash.h"

namespace uking::action {

SiteBossSwordWhirlSlash::SiteBossSwordWhirlSlash(const InitArg& arg)
    : SiteBossSwordAttackBase(arg) {}

SiteBossSwordWhirlSlash::~SiteBossSwordWhirlSlash() = default;

bool SiteBossSwordWhirlSlash::init_(sead::Heap* heap) {
    return SiteBossSwordAttackBase::init_(heap);
}

void SiteBossSwordWhirlSlash::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossSwordAttackBase::enter_(params);
}

void SiteBossSwordWhirlSlash::leave_() {
    SiteBossSwordAttackBase::leave_();
}

void SiteBossSwordWhirlSlash::loadParams_() {
    SiteBossSwordAttackBase::loadParams_();
}

void SiteBossSwordWhirlSlash::calc_() {
    SiteBossSwordAttackBase::calc_();
}

}  // namespace uking::action
