#include "Game/AI/Action/actionWalk.h"

namespace uking::action {

Walk::Walk(const InitArg& arg) : MoveBase(arg) {}

void Walk::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

}  // namespace uking::action
