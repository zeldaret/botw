#include "Game/AI/Action/actionGuardTurn.h"

namespace uking::action {

GuardTurn::GuardTurn(const InitArg& arg) : TurnBase(arg) {}

void GuardTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
}

}  // namespace uking::action
