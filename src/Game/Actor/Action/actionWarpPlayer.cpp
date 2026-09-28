#include "Game/Actor/Action/actionWarpPlayer.h"

namespace uking::action {

WarpPlayer::WarpPlayer(const InitArg& arg) : DestPlayerWarpBase(arg) {}

WarpPlayer::~WarpPlayer() = default;

bool WarpPlayer::init_(sead::Heap* heap) {
    return DestPlayerWarpBase::init_(heap);
}

void WarpPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    DestPlayerWarpBase::enter_(params);
}

void WarpPlayer::leave_() {
    DestPlayerWarpBase::leave_();
}

void WarpPlayer::loadParams_() {
    DestPlayerWarpBase::loadParams_();
    getDynamicParam(&mWarpDestMapName_d, "WarpDestMapName");
    getDynamicParam(&mWarpDestPosName_d, "WarpDestPosName");
}

void WarpPlayer::calc_() {
    DestPlayerWarpBase::calc_();
}

}  // namespace uking::action
