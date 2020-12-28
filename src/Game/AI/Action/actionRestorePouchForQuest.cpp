#include "Game/AI/Action/actionRestorePouchForQuest.h"

namespace uking::action {

RestorePouchForQuest::RestorePouchForQuest(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RestorePouchForQuest::~RestorePouchForQuest() = default;

bool RestorePouchForQuest::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RestorePouchForQuest::loadParams_() {}

}  // namespace uking::action
