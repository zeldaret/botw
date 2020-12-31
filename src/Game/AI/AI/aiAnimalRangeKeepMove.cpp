#include "Game/AI/AI/aiAnimalRangeKeepMove.h"

namespace uking::ai {

AnimalRangeKeepMove::AnimalRangeKeepMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalRangeKeepMove::~AnimalRangeKeepMove() = default;

bool AnimalRangeKeepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AnimalRangeKeepMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalRangeKeepMove::loadParams_() {
    getStaticParam(&mBattleEndTimerMin_s, "BattleEndTimerMin");
    getStaticParam(&mBattleEndTimerMax_s, "BattleEndTimerMax");
    getStaticParam(&mCloseStartDist_s, "CloseStartDist");
    getStaticParam(&mCloseEndDist_s, "CloseEndDist");
    getStaticParam(&mLeaveStartDist_s, "LeaveStartDist");
    getStaticParam(&mLeaveEndDist_s, "LeaveEndDist");
    getStaticParam(&mBattleEndDist_s, "BattleEndDist");
}

}  // namespace uking::ai
