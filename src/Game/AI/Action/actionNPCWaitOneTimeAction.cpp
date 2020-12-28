#include "Game/AI/Action/actionNPCWaitOneTimeAction.h"

namespace uking::action {

NPCWaitOneTimeAction::NPCWaitOneTimeAction(const InitArg& arg) : NPCWait(arg) {}

NPCWaitOneTimeAction::~NPCWaitOneTimeAction() = default;

void NPCWaitOneTimeAction::calc_() {
    NPCWait::calc_();
}

}  // namespace uking::action
