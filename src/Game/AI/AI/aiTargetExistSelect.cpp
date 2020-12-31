#include "Game/AI/AI/aiTargetExistSelect.h"

namespace uking::ai {

TargetExistSelect::TargetExistSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetExistSelect::~TargetExistSelect() = default;

bool TargetExistSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetExistSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetExistSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetExistSelect::loadParams_() {}

}  // namespace uking::ai
