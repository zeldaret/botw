#include "Game/AI/Action/actionInitPouchForQuest.h"

namespace uking::action {

InitPouchForQuest::InitPouchForQuest(const InitArg& arg) : ksys::act::ai::Action(arg) {}

InitPouchForQuest::~InitPouchForQuest() = default;

bool InitPouchForQuest::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void InitPouchForQuest::loadParams_() {}

}  // namespace uking::action
