#include "Game/AI/AI/aiPreyDeadCauseSelector.h"

namespace uking::ai {

PreyDeadCauseSelector::PreyDeadCauseSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyDeadCauseSelector::~PreyDeadCauseSelector() = default;

bool PreyDeadCauseSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreyDeadCauseSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PreyDeadCauseSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreyDeadCauseSelector::loadParams_() {}

}  // namespace uking::ai
