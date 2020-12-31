#include "Game/AI/AI/aiTargetOnMovableNavmeshSelect.h"

namespace uking::ai {

TargetOnMovableNavmeshSelect::TargetOnMovableNavmeshSelect(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

TargetOnMovableNavmeshSelect::~TargetOnMovableNavmeshSelect() = default;

bool TargetOnMovableNavmeshSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetOnMovableNavmeshSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetOnMovableNavmeshSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetOnMovableNavmeshSelect::loadParams_() {
    getStaticParam(&mCheckDist_s, "CheckDist");
    getStaticParam(&mOnStopCheckDist_s, "OnStopCheckDist");
}

}  // namespace uking::ai
