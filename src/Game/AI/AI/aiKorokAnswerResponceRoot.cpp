#include "Game/AI/AI/aiKorokAnswerResponceRoot.h"

namespace uking::ai {

KorokAnswerResponceRoot::KorokAnswerResponceRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokAnswerResponceRoot::~KorokAnswerResponceRoot() = default;

bool KorokAnswerResponceRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokAnswerResponceRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void KorokAnswerResponceRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokAnswerResponceRoot::loadParams_() {
    getMapUnitParam(&mEffectDispSize_m, "EffectDispSize");
    getMapUnitParam(&mIsNoResponceSound_m, "IsNoResponceSound");
    getMapUnitParam(&mEffectDispActorName_m, "EffectDispActorName");
    getMapUnitParam(&mEffectDIspOffset_m, "EffectDIspOffset");
}

}  // namespace uking::ai
