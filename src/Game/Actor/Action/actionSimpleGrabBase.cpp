#include "Game/Actor/Action/actionSimpleGrabBase.h"

namespace uking::action {

SimpleGrabBase::SimpleGrabBase(const InitArg& arg) : Grab(arg) {}

SimpleGrabBase::~SimpleGrabBase() = default;

void SimpleGrabBase::loadParams_() {
    Grab::loadParams_();
}

}  // namespace uking::action
