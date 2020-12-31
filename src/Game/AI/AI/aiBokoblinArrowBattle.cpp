#include "Game/AI/AI/aiBokoblinArrowBattle.h"

namespace uking::ai {

BokoblinArrowBattle::BokoblinArrowBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BokoblinArrowBattle::~BokoblinArrowBattle() = default;

void BokoblinArrowBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BokoblinArrowBattle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BokoblinArrowBattle::loadParams_() {
    getStaticParam(&mHoldInterval_s, "HoldInterval");
    getStaticParam(&mHoldIntervalLast_s, "HoldIntervalLast");
    getStaticParam(&mHoldIntervalRand_s, "HoldIntervalRand");
    getStaticParam(&mLeaveStartDist_s, "LeaveStartDist");
    getStaticParam(&mLeaveEndDist_s, "LeaveEndDist");
    getStaticParam(&mLeaveWaitTime_s, "LeaveWaitTime");
    getStaticParam(&mLeaveTime_s, "LeaveTime");
    getStaticParam(&mBaseDist_s, "BaseDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mOutDistVMin_s, "OutDistVMin");
    getStaticParam(&mOutDistVMax_s, "OutDistVMax");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mLeaveTime_s, "LeaveTime");
    getStaticParam(&mBlindlyAttackMinNum_s, "BlindlyAttackMinNum");
    getStaticParam(&mBlindlyAttackMaxNum_s, "BlindlyAttackMaxNum");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mShootDistRatio_s, "ShootDistRatio");
    getStaticParam(&mIsEndAfterAttack_s, "IsEndAfterAttack");
    getStaticParam(&mIsUpdateNoticeState_s, "IsUpdateNoticeState");
}

}  // namespace uking::ai
