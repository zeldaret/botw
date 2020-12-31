#include "Game/AI/AI/aiTargetInAreaSelect.h"

namespace uking::ai {

TargetInAreaSelect::TargetInAreaSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetInAreaSelect::~TargetInAreaSelect() = default;

bool TargetInAreaSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetInAreaSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetInAreaSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetInAreaSelect::loadParams_() {
    getStaticParam(&mOption_s, "Option");
}

}  // namespace uking::ai
