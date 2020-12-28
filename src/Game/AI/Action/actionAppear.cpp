#include "Game/AI/Action/actionAppear.h"

namespace uking::action {

Appear::Appear(const InitArg& arg) : ActionWithAS(arg) {}

void Appear::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

}  // namespace uking::action
