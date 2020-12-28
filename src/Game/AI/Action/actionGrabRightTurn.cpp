#include "Game/AI/Action/actionGrabRightTurn.h"

namespace uking::action {

GrabRightTurn::GrabRightTurn(const InitArg& arg) : TurnBase(arg) {}

void GrabRightTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    TurnBase::enter_(params);
}

}  // namespace uking::action
