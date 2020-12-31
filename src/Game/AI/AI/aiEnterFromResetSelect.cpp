#include "Game/AI/AI/aiEnterFromResetSelect.h"

namespace uking::ai {

EnterFromResetSelect::EnterFromResetSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnterFromResetSelect::~EnterFromResetSelect() = default;

bool EnterFromResetSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnterFromResetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnterFromResetSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnterFromResetSelect::loadParams_() {}

}  // namespace uking::ai
