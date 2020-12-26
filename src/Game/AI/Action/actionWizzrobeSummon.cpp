#include "Game/AI/Action/actionWizzrobeSummon.h"

namespace uking::action {

WizzrobeSummon::WizzrobeSummon(const InitArg& arg) : TurnIgnite(arg) {}

WizzrobeSummon::~WizzrobeSummon() = default;

bool WizzrobeSummon::init_(sead::Heap* heap) {
    return TurnIgnite::init_(heap);
}

void WizzrobeSummon::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnIgnite::enter_(params);
}

void WizzrobeSummon::leave_() {
    TurnIgnite::leave_();
}

void WizzrobeSummon::loadParams_() {
    TurnIgnite::loadParams_();
    getStaticParam(&mSummonBufferSize_s, "SummonBufferSize");
    getStaticParam(&mWeaponIndex_s, "WeaponIndex");
    getStaticParam(&mSummonBufferKey_s, "SummonBufferKey");
    getAITreeVariable(&mSummonCount_a, "SummonCount");
}

void WizzrobeSummon::calc_() {
    TurnIgnite::calc_();
}

}  // namespace uking::action
