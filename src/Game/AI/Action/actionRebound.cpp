#include "Game/AI/Action/actionRebound.h"

namespace uking::action {

Rebound::Rebound(const InitArg& arg) : ActionWithAS(arg) {}

void Rebound::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

}  // namespace uking::action
