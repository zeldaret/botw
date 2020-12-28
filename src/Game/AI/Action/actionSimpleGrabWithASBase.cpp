#include "Game/AI/Action/actionSimpleGrabWithASBase.h"

namespace uking::action {

SimpleGrabWithASBase::SimpleGrabWithASBase(const InitArg& arg) : Grab(arg) {}

SimpleGrabWithASBase::~SimpleGrabWithASBase() = default;

void SimpleGrabWithASBase::loadParams_() {
    Grab::loadParams_();
}

}  // namespace uking::action
