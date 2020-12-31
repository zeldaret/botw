#include "Game/AI/AI/aiTrgTargetChangeToPlayerSelect.h"

namespace uking::ai {

TrgTargetChangeToPlayerSelect::TrgTargetChangeToPlayerSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

TrgTargetChangeToPlayerSelect::~TrgTargetChangeToPlayerSelect() = default;

bool TrgTargetChangeToPlayerSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TrgTargetChangeToPlayerSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TrgTargetChangeToPlayerSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TrgTargetChangeToPlayerSelect::loadParams_() {
    getAITreeVariable(&mIsTrgTargetChangeToPlayer_a, "IsTrgTargetChangeToPlayer");
}

}  // namespace uking::ai
