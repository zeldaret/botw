#include "Game/AI/Action/actionWarpToGameDataVec3f.h"

namespace uking::action {

WarpToGameDataVec3f::WarpToGameDataVec3f(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToGameDataVec3f::~WarpToGameDataVec3f() = default;

bool WarpToGameDataVec3f::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToGameDataVec3f::loadParams_() {
    getDynamicParam(&mDestinationX_d, "DestinationX");
    getDynamicParam(&mDestinationY_d, "DestinationY");
    getDynamicParam(&mDestinationZ_d, "DestinationZ");
    getDynamicParam(&mDirectionY_d, "DirectionY");
    getDynamicParam(&mRotToVec3f_d, "RotToVec3f");
    getDynamicParam(&mGameDataVec3fWarpToPos_d, "GameDataVec3fWarpToPos");
    getDynamicParam(&mGameDataVec3fRotDir_d, "GameDataVec3fRotDir");
}

}  // namespace uking::action
