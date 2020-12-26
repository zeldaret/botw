#include "Game/AI/Action/actionActorInfoToGameDataVec3.h"

namespace uking::action {

ActorInfoToGameDataVec3::ActorInfoToGameDataVec3(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ActorInfoToGameDataVec3::~ActorInfoToGameDataVec3() = default;

bool ActorInfoToGameDataVec3::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ActorInfoToGameDataVec3::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ActorInfoToGameDataVec3::leave_() {
    ksys::act::ai::Action::leave_();
}

void ActorInfoToGameDataVec3::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mGameDataVec3fToName_d, "GameDataVec3fToName");
    getDynamicParam(&mParameterName_d, "ParameterName");
}

void ActorInfoToGameDataVec3::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
