#include "Game/AI/AI/aiAnimalRangeKeepMoveWithLOS.h"

namespace uking::ai {

AnimalRangeKeepMoveWithLOS::AnimalRangeKeepMoveWithLOS(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

AnimalRangeKeepMoveWithLOS::~AnimalRangeKeepMoveWithLOS() = default;

bool AnimalRangeKeepMoveWithLOS::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalRangeKeepMoveWithLOS::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AnimalRangeKeepMoveWithLOS::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalRangeKeepMoveWithLOS::loadParams_() {
    getStaticParam(&mFindPathBeginTimer_s, "FindPathBeginTimer");
    getStaticParam(&mNoPathTimer_s, "NoPathTimer");
    getStaticParam(&mCloseStartDist_s, "CloseStartDist");
    getStaticParam(&mCloseEndDist_s, "CloseEndDist");
    getStaticParam(&mLeaveStartDist_s, "LeaveStartDist");
    getStaticParam(&mLeaveEndDist_s, "LeaveEndDist");
    getStaticParam(&mBattleEndDist_s, "BattleEndDist");
    getStaticParam(&mDistFailOnUnreachablePath_s, "DistFailOnUnreachablePath");
}

}  // namespace uking::ai
