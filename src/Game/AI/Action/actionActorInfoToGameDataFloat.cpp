#include "Game/AI/Action/actionActorInfoToGameDataFloat.h"

namespace uking::action {

ActorInfoToGameDataFloat::ActorInfoToGameDataFloat(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ActorInfoToGameDataFloat::~ActorInfoToGameDataFloat() = default;

bool ActorInfoToGameDataFloat::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ActorInfoToGameDataFloat::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ActorInfoToGameDataFloat::leave_() {
    ksys::act::ai::Action::leave_();
}

void ActorInfoToGameDataFloat::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mGameDataFloatToName_d, "GameDataFloatToName");
    getDynamicParam(&mParameterName_d, "ParameterName");
}

void ActorInfoToGameDataFloat::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
