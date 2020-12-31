#include "Game/AI/AI/aiArrow.h"

namespace uking::ai {

Arrow::Arrow(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

Arrow::~Arrow() = default;

bool Arrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void Arrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void Arrow::leave_() {
    ksys::act::ai::Ai::leave_();
}

void Arrow::loadParams_() {}

}  // namespace uking::ai
