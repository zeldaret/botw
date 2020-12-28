#include "Game/AI/Action/actionSetPlayerDrawingSword.h"

namespace uking::action {

SetPlayerDrawingSword::SetPlayerDrawingSword(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetPlayerDrawingSword::~SetPlayerDrawingSword() = default;

bool SetPlayerDrawingSword::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetPlayerDrawingSword::loadParams_() {}

}  // namespace uking::action
