#include "Game/Actor/Action/actionDisappearAndEscapeBase.h"

namespace uking::action {

DisappearAndEscapeBase::DisappearAndEscapeBase(const InitArg& arg) : ActionWithAS(arg) {}

DisappearAndEscapeBase::~DisappearAndEscapeBase() = default;

bool DisappearAndEscapeBase::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void DisappearAndEscapeBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void DisappearAndEscapeBase::leave_() {
    ActionWithAS::leave_();
}

void DisappearAndEscapeBase::loadParams_() {
    StopBase::loadParams_();
}

void DisappearAndEscapeBase::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
