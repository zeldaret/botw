#include "Game/AI/AI/aiRandomSelectTwoActionBase.h"

namespace uking::ai {

RandomSelectTwoActionBase::RandomSelectTwoActionBase(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RandomSelectTwoActionBase::~RandomSelectTwoActionBase() = default;

bool RandomSelectTwoActionBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RandomSelectTwoActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RandomSelectTwoActionBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RandomSelectTwoActionBase::loadParams_() {
    getStaticParam(&mCorrectRateToA_s, "CorrectRateToA");
    getStaticParam(&mCorrectRateToB_s, "CorrectRateToB");
}

}  // namespace uking::ai
