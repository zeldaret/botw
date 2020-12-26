#include "Game/AI/Action/actionGetItemAnotherActor.h"

namespace uking::action {

GetItemAnotherActor::GetItemAnotherActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GetItemAnotherActor::~GetItemAnotherActor() = default;

bool GetItemAnotherActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GetItemAnotherActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GetItemAnotherActor::leave_() {
    ksys::act::ai::Action::leave_();
}

void GetItemAnotherActor::loadParams_() {
    getDynamicParam(&mGetActorName_d, "GetActorName");
    getAITreeVariable(&mGetNumLeft_a, "GetNumLeft");
}

void GetItemAnotherActor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
