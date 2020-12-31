#include "Game/AI/AI/aiArrowDelete.h"

namespace uking::ai {

ArrowDelete::ArrowDelete(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ArrowDelete::~ArrowDelete() = default;

bool ArrowDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ArrowDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ArrowDelete::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ArrowDelete::loadParams_() {}

}  // namespace uking::ai
