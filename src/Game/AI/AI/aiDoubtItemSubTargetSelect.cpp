#include "Game/AI/AI/aiDoubtItemSubTargetSelect.h"

namespace uking::ai {

DoubtItemSubTargetSelect::DoubtItemSubTargetSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DoubtItemSubTargetSelect::~DoubtItemSubTargetSelect() = default;

bool DoubtItemSubTargetSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DoubtItemSubTargetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DoubtItemSubTargetSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DoubtItemSubTargetSelect::loadParams_() {}

}  // namespace uking::ai
