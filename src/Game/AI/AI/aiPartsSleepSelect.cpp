#include "Game/AI/AI/aiPartsSleepSelect.h"

namespace uking::ai {

PartsSleepSelect::PartsSleepSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PartsSleepSelect::~PartsSleepSelect() = default;

bool PartsSleepSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PartsSleepSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PartsSleepSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PartsSleepSelect::loadParams_() {
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::ai
