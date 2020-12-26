#include "Game/AI/Action/actionCreateObjectsOfOwnedHorse.h"

namespace uking::action {

CreateObjectsOfOwnedHorse::CreateObjectsOfOwnedHorse(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CreateObjectsOfOwnedHorse::~CreateObjectsOfOwnedHorse() = default;

bool CreateObjectsOfOwnedHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CreateObjectsOfOwnedHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CreateObjectsOfOwnedHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void CreateObjectsOfOwnedHorse::loadParams_() {
    getDynamicParam(&mHorseReinsActorName_d, "HorseReinsActorName");
    getDynamicParam(&mHorseSaddleActorName_d, "HorseSaddleActorName");
    getDynamicParam(&mHorseManeActorName_d, "HorseManeActorName");
}

void CreateObjectsOfOwnedHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
