#include "Game/AI/AI/aiCookPotRoot.h"

namespace uking::ai {

CookPotRoot::CookPotRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CookPotRoot::~CookPotRoot() = default;

bool CookPotRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CookPotRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CookPotRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CookPotRoot::loadParams_() {
    getMapUnitParam(&mInitBurnState_m, "InitBurnState");
    getAITreeVariable(&mCurrentCookResultHolder_a, "CurrentCookResultHolder");
}

}  // namespace uking::ai
