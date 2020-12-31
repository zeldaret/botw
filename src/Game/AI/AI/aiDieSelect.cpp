#include "Game/AI/AI/aiDieSelect.h"

namespace uking::ai {

DieSelect::DieSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DieSelect::~DieSelect() = default;

bool DieSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DieSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DieSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DieSelect::loadParams_() {}

}  // namespace uking::ai
