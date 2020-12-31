#include "Game/AI/AI/aiActorWaterDepthSelect.h"

namespace uking::ai {

ActorWaterDepthSelect::ActorWaterDepthSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ActorWaterDepthSelect::~ActorWaterDepthSelect() = default;

bool ActorWaterDepthSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ActorWaterDepthSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ActorWaterDepthSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ActorWaterDepthSelect::loadParams_() {
    getStaticParam(&mDeepDepth_s, "DeepDepth");
    getStaticParam(&mOnEnterOnly_s, "OnEnterOnly");
    getStaticParam(&mForceDeepChange_s, "ForceDeepChange");
}

}  // namespace uking::ai
