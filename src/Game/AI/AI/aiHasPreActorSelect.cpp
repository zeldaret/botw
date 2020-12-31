#include "Game/AI/AI/aiHasPreActorSelect.h"

namespace uking::ai {

HasPreActorSelect::HasPreActorSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HasPreActorSelect::~HasPreActorSelect() = default;

bool HasPreActorSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HasPreActorSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void HasPreActorSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HasPreActorSelect::loadParams_() {}

}  // namespace uking::ai
