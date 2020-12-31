#include "Game/AI/AI/aiWindGenerator.h"

namespace uking::ai {

WindGenerator::WindGenerator(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool WindGenerator::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WindGenerator::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WindGenerator::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WindGenerator::loadParams_() {}

}  // namespace uking::ai
