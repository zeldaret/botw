#include "Game/AI/AI/aiRandomSelectThreeActionBase.h"

namespace uking::ai {

RandomSelectThreeActionBase::RandomSelectThreeActionBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RandomSelectThreeActionBase::~RandomSelectThreeActionBase() = default;

bool RandomSelectThreeActionBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RandomSelectThreeActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RandomSelectThreeActionBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RandomSelectThreeActionBase::loadParams_() {
    getStaticParam(&mCorrectRatioA_s, "CorrectRatioA");
    getStaticParam(&mCorrectRatioB_s, "CorrectRatioB");
    getStaticParam(&mCorrectRatioC_s, "CorrectRatioC");
}

}  // namespace uking::ai
