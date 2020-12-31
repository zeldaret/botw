#include "Game/AI/AI/aiCapturedActDeadSelector.h"

namespace uking::ai {

CapturedActDeadSelector::CapturedActDeadSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CapturedActDeadSelector::~CapturedActDeadSelector() = default;

bool CapturedActDeadSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CapturedActDeadSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CapturedActDeadSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CapturedActDeadSelector::loadParams_() {
    getMapUnitParam(&mIsPlayerPut_m, "IsPlayerPut");
    // FIXME: CALL _ZNK4ksys3act2ai6RootAi18getAITreeVariable2EPPbRKN4sead14SafeStringBaseIcEE @
    // 0x7100d66968
}

}  // namespace uking::ai
