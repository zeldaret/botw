#include "Game/AI/Action/actionActorInfoToGameDataVec3.h"

namespace uking::action {

ActorInfoToGameDataVec3::ActorInfoToGameDataVec3(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ActorInfoToGameDataVec3::~ActorInfoToGameDataVec3() = default;

bool ActorInfoToGameDataVec3::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ActorInfoToGameDataVec3::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mGameDataVec3fToName_d, "GameDataVec3fToName");
    getDynamicParam(&mParameterName_d, "ParameterName");
}

}  // namespace uking::action
