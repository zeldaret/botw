#include "Game/AI/AI/aiKorokRailMove.h"

namespace uking::ai {

KorokRailMove::KorokRailMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokRailMove::~KorokRailMove() = default;

bool KorokRailMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokRailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void KorokRailMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokRailMove::loadParams_() {
    getStaticParam(&mOnRailDistance_s, "OnRailDistance");
    getStaticParam(&mFarDistance_s, "FarDistance");
    getStaticParam(&mIsIgnoreNoWaitStopPoint_s, "IsIgnoreNoWaitStopPoint");
    getMapUnitParam(&mRailMoveSpeed_m, "RailMoveSpeed");
}

}  // namespace uking::ai
