#include "Game/AI/AI/aiTargetPosOnNavFaceSelect.h"

namespace uking::ai {

TargetPosOnNavFaceSelect::TargetPosOnNavFaceSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetPosOnNavFaceSelect::~TargetPosOnNavFaceSelect() = default;

bool TargetPosOnNavFaceSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetPosOnNavFaceSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetPosOnNavFaceSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetPosOnNavFaceSelect::loadParams_() {
    getStaticParam(&mSearchRadius_s, "SearchRadius");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
