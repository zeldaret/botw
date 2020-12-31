#include "Game/AI/AI/aiStalPartNormal.h"

namespace uking::ai {

StalPartNormal::StalPartNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalPartNormal::~StalPartNormal() = default;

bool StalPartNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalPartNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalPartNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalPartNormal::loadParams_() {
    getStaticParam(&mTerritoryArea_s, "TerritoryArea");
    getStaticParam(&mCatchArea_s, "CatchArea");
    getStaticParam(&mWaitTimer_s, "WaitTimer");
    getStaticParam(&mTgtOffset_s, "TgtOffset");
}

}  // namespace uking::ai
