#include "Game/AI/AI/aiCapturedActorReactionChemical.h"

namespace uking::ai {

CapturedActorReactionChemical::CapturedActorReactionChemical(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

CapturedActorReactionChemical::~CapturedActorReactionChemical() = default;

bool CapturedActorReactionChemical::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CapturedActorReactionChemical::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CapturedActorReactionChemical::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CapturedActorReactionChemical::loadParams_() {
    getStaticParam(&mOnEnterOnly_s, "OnEnterOnly");
}

}  // namespace uking::ai
