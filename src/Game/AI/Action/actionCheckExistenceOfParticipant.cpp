#include "Game/AI/Action/actionCheckExistenceOfParticipant.h"

namespace uking::action {

CheckExistenceOfParticipant::CheckExistenceOfParticipant(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CheckExistenceOfParticipant::~CheckExistenceOfParticipant() = default;

bool CheckExistenceOfParticipant::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CheckExistenceOfParticipant::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CheckExistenceOfParticipant::leave_() {
    ksys::act::ai::Action::leave_();
}

void CheckExistenceOfParticipant::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mInstanceName_d, "InstanceName");
}

void CheckExistenceOfParticipant::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
