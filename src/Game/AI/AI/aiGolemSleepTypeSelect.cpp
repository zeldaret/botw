#include "Game/AI/AI/aiGolemSleepTypeSelect.h"

namespace uking::ai {

GolemSleepTypeSelect::GolemSleepTypeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemSleepTypeSelect::~GolemSleepTypeSelect() = default;

bool GolemSleepTypeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolemSleepTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GolemSleepTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemSleepTypeSelect::loadParams_() {
    getMapUnitParam(&mGolemSleepType_m, "GolemSleepType");
}

}  // namespace uking::ai
