#include "Game/AI/AI/aiEscapeOrWaitSelect.h"

namespace uking::ai {

EscapeOrWaitSelect::EscapeOrWaitSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EscapeOrWaitSelect::~EscapeOrWaitSelect() = default;

bool EscapeOrWaitSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EscapeOrWaitSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EscapeOrWaitSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EscapeOrWaitSelect::loadParams_() {
    getStaticParam(&mEscapeRange_s, "EscapeRange");
    getStaticParam(&mEscapeMoveDistMin_s, "EscapeMoveDistMin");
    getStaticParam(&mEscapeMoveDistMax_s, "EscapeMoveDistMax");
    getStaticParam(&mCheckBackAngle_s, "CheckBackAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
