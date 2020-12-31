#include "Game/AI/AI/aiTargetPosDirLRSelect.h"

namespace uking::ai {

TargetPosDirLRSelect::TargetPosDirLRSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetPosDirLRSelect::~TargetPosDirLRSelect() = default;

bool TargetPosDirLRSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetPosDirLRSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetPosDirLRSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetPosDirLRSelect::loadParams_() {
    getStaticParam(&mIsCheckEveryFrame_s, "IsCheckEveryFrame");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
