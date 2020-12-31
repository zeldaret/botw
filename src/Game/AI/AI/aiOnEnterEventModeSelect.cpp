#include "Game/AI/AI/aiOnEnterEventModeSelect.h"

namespace uking::ai {

OnEnterEventModeSelect::OnEnterEventModeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OnEnterEventModeSelect::~OnEnterEventModeSelect() = default;

bool OnEnterEventModeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OnEnterEventModeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void OnEnterEventModeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OnEnterEventModeSelect::loadParams_() {}

}  // namespace uking::ai
