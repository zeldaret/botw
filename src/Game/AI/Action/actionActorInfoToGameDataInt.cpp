#include "Game/AI/Action/actionActorInfoToGameDataInt.h"

namespace uking::action {

ActorInfoToGameDataInt::ActorInfoToGameDataInt(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ActorInfoToGameDataInt::~ActorInfoToGameDataInt() = default;

bool ActorInfoToGameDataInt::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ActorInfoToGameDataInt::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ActorInfoToGameDataInt::leave_() {
    ksys::act::ai::Action::leave_();
}

void ActorInfoToGameDataInt::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mGameDataIntToName_d, "GameDataIntToName");
    getDynamicParam(&mParameterName_d, "ParameterName");
}

void ActorInfoToGameDataInt::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
