#include "Game/AI/AI/aiKorokTargetRailMove.h"

namespace uking::ai {

KorokTargetRailMove::KorokTargetRailMove(const InitArg& arg) : KorokRailMove(arg) {}

KorokTargetRailMove::~KorokTargetRailMove() = default;

bool KorokTargetRailMove::init_(sead::Heap* heap) {
    return KorokRailMove::init_(heap);
}

void KorokTargetRailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    KorokRailMove::enter_(params);
}

void KorokTargetRailMove::leave_() {
    KorokRailMove::leave_();
}

void KorokTargetRailMove::loadParams_() {
    KorokRailMove::loadParams_();
    getStaticParam(&mRotSpd_s, "RotSpd");
    getMapUnitParam(&mKorokTargetAppearFrame_m, "KorokTargetAppearFrame");
    getMapUnitParam(&mKorokTargetVanishFrame_m, "KorokTargetVanishFrame");
    getMapUnitParam(&mIsNoAppearEffect_m, "IsNoAppearEffect");
}

}  // namespace uking::ai
