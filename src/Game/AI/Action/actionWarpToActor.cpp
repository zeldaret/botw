#include "Game/AI/Action/actionWarpToActor.h"

namespace uking::action {

WarpToActor::WarpToActor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToActor::~WarpToActor() = default;

bool WarpToActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpToActor::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpToActor::loadParams_() {
    getDynamicParam(&mDestinationX_d, "DestinationX");
    getDynamicParam(&mDestinationY_d, "DestinationY");
    getDynamicParam(&mDestinationZ_d, "DestinationZ");
    getDynamicParam(&mDirectionY_d, "DirectionY");
    getDynamicParam(&mRotToVec3f_d, "RotToVec3f");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mGameDataVec3fRotDir_d, "GameDataVec3fRotDir");
}

void WarpToActor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
