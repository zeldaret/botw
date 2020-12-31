#include "Game/AI/AI/aiMimicryResetCheck.h"

namespace uking::ai {

MimicryResetCheck::MimicryResetCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MimicryResetCheck::~MimicryResetCheck() = default;

void MimicryResetCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MimicryResetCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MimicryResetCheck::loadParams_() {
    getStaticParam(&mResetRate_s, "ResetRate");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

}  // namespace uking::ai
