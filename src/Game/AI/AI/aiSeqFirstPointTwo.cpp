#include "Game/AI/AI/aiSeqFirstPointTwo.h"

namespace uking::ai {

SeqFirstPointTwo::SeqFirstPointTwo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SeqFirstPointTwo::~SeqFirstPointTwo() = default;

bool SeqFirstPointTwo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SeqFirstPointTwo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SeqFirstPointTwo::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SeqFirstPointTwo::loadParams_() {
    getStaticParam(&mIsFinishedByFailAction_s, "IsFinishedByFailAction");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
