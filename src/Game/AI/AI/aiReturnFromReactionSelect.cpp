#include "Game/AI/AI/aiReturnFromReactionSelect.h"

namespace uking::ai {

ReturnFromReactionSelect::ReturnFromReactionSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReturnFromReactionSelect::~ReturnFromReactionSelect() = default;

bool ReturnFromReactionSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReturnFromReactionSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ReturnFromReactionSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ReturnFromReactionSelect::loadParams_() {
    getStaticParam(&mIsChangeToNormalByFinish_s, "IsChangeToNormalByFinish");
    getStaticParam(&mIsEnableRetFromDamage_s, "IsEnableRetFromDamage");
    getStaticParam(&mIsEnableRetFromGuard_s, "IsEnableRetFromGuard");
    getStaticParam(&mIsEnableRetFromRebound_s, "IsEnableRetFromRebound");
}

}  // namespace uking::ai
