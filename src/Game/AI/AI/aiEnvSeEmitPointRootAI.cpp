#include "Game/AI/AI/aiEnvSeEmitPointRootAI.h"

namespace uking::ai {

EnvSeEmitPointRootAI::EnvSeEmitPointRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnvSeEmitPointRootAI::~EnvSeEmitPointRootAI() = default;

bool EnvSeEmitPointRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnvSeEmitPointRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnvSeEmitPointRootAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnvSeEmitPointRootAI::loadParams_() {
    getStaticParam(&mInvalidatePlayDistance_s, "InvalidatePlayDistance");
    getStaticParam(&mPlayDistance_s, "PlayDistance");
}

}  // namespace uking::ai
