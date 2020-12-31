#include "Game/AI/AI/aiPrevASEndSeq.h"

namespace uking::ai {

PrevASEndSeq::PrevASEndSeq(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PrevASEndSeq::~PrevASEndSeq() = default;

bool PrevASEndSeq::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PrevASEndSeq::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PrevASEndSeq::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PrevASEndSeq::loadParams_() {
    getStaticParam(&mPrevASName_s, "PrevASName");
}

}  // namespace uking::ai
