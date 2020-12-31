#include "Game/AI/AI/aiAssassinBossEscapeFromTarget.h"

namespace uking::ai {

AssassinBossEscapeFromTarget::AssassinBossEscapeFromTarget(const InitArg& arg)
    : SimpleEscapeFromTarget(arg) {}

AssassinBossEscapeFromTarget::~AssassinBossEscapeFromTarget() = default;

bool AssassinBossEscapeFromTarget::init_(sead::Heap* heap) {
    return SimpleEscapeFromTarget::init_(heap);
}

void AssassinBossEscapeFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleEscapeFromTarget::enter_(params);
}

void AssassinBossEscapeFromTarget::leave_() {
    SimpleEscapeFromTarget::leave_();
}

void AssassinBossEscapeFromTarget::loadParams_() {
    SimpleEscapeFromTarget::loadParams_();
    getStaticParam(&mAnchorName_s, "AnchorName");
    getStaticParam(&mCheckDist_s, "CheckDist");
}

}  // namespace uking::ai
