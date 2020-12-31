#include "Game/AI/AI/aiOnRagdollSelect.h"

namespace uking::ai {

OnRagdollSelect::OnRagdollSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OnRagdollSelect::~OnRagdollSelect() = default;

bool OnRagdollSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OnRagdollSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void OnRagdollSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OnRagdollSelect::loadParams_() {}

}  // namespace uking::ai
