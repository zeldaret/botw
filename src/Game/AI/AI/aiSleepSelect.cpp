#include "Game/AI/AI/aiSleepSelect.h"

namespace uking::ai {

SleepSelect::SleepSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SleepSelect::~SleepSelect() = default;

bool SleepSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SleepSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SleepSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SleepSelect::loadParams_() {}

}  // namespace uking::ai
