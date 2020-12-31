#include "Game/AI/AI/aiKokkoAngryTargetSelect.h"

namespace uking::ai {

KokkoAngryTargetSelect::KokkoAngryTargetSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KokkoAngryTargetSelect::~KokkoAngryTargetSelect() = default;

bool KokkoAngryTargetSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KokkoAngryTargetSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void KokkoAngryTargetSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KokkoAngryTargetSelect::loadParams_() {}

}  // namespace uking::ai
