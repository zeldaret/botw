#include "Game/AI/Action/actionNoDeleteCurrentActor.h"

namespace uking::action {

NoDeleteCurrentActor::NoDeleteCurrentActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NoDeleteCurrentActor::~NoDeleteCurrentActor() = default;

bool NoDeleteCurrentActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NoDeleteCurrentActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NoDeleteCurrentActor::leave_() {
    ksys::act::ai::Action::leave_();
}

void NoDeleteCurrentActor::loadParams_() {}

void NoDeleteCurrentActor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
