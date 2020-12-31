#include "Game/AI/AI/aiHiddenKorokRoot.h"

namespace uking::ai {

HiddenKorokRoot::HiddenKorokRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HiddenKorokRoot::~HiddenKorokRoot() = default;

bool HiddenKorokRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HiddenKorokRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HiddenKorokRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HiddenKorokRoot::loadParams_() {
    getStaticParam(&mPainTalkHitSpeed_s, "PainTalkHitSpeed");
    getStaticParam(&mPainTalkDistance_s, "PainTalkDistance");
    getMapUnitParam(&mKorokEventStartWaitFrame_m, "KorokEventStartWaitFrame");
    getMapUnitParam(&mIsAppearCheck_m, "IsAppearCheck");
    getMapUnitParam(&mPlacementType_m, "PlacementType");
    getMapUnitParam(&mIsHiddenKorokLiftAppear_m, "IsHiddenKorokLiftAppear");
    getMapUnitParam(&mIsInvisibleKorok_m, "IsInvisibleKorok");
}

}  // namespace uking::ai
