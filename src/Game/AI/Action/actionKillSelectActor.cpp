#include "Game/AI/Action/actionKillSelectActor.h"

namespace uking::action {

KillSelectActor::KillSelectActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KillSelectActor::~KillSelectActor() = default;

bool KillSelectActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KillSelectActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KillSelectActor::leave_() {
    ksys::act::ai::Action::leave_();
}

void KillSelectActor::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

void KillSelectActor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
