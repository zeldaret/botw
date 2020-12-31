#include "Game/AI/AI/aiPrevASOR2SelectTwo.h"

namespace uking::ai {

PrevASOR2SelectTwo::PrevASOR2SelectTwo(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PrevASOR2SelectTwo::~PrevASOR2SelectTwo() = default;

bool PrevASOR2SelectTwo::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PrevASOR2SelectTwo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PrevASOR2SelectTwo::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PrevASOR2SelectTwo::loadParams_() {
    getStaticParam(&mAS1_s, "AS1");
    getStaticParam(&mAS2_s, "AS2");
}

}  // namespace uking::ai
