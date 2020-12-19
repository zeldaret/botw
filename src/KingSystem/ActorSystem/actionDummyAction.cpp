#include "KingSystem/ActorSystem/actionDummyAction.h"

namespace ksys::act::ai {

DummyAction::DummyAction(const InitArg& arg) : Action(arg) {}

void DummyAction::enter_(InlineParamPack* params) {
    mFlags.set(ActionBase::Flag::_4);
}

void DummyAction::calc_() {}

void DummyAction::leave_() {}

void DummyAction::loadParams_() {}

}  // namespace ksys::act::ai
