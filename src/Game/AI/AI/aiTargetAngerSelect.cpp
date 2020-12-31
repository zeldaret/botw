#include "Game/AI/AI/aiTargetAngerSelect.h"

namespace uking::ai {

TargetAngerSelect::TargetAngerSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetAngerSelect::~TargetAngerSelect() = default;

bool TargetAngerSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetAngerSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetAngerSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetAngerSelect::loadParams_() {}

}  // namespace uking::ai
