#include "Game/Actor/Action/actionActionWithAS.h"

namespace uking::action {

ActionWithAS::ActionWithAS(const InitArg& arg) : StopBase(arg) {}

void ActionWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void ActionWithAS::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
