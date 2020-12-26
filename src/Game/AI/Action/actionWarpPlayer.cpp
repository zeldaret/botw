#include "Game/AI/Action/actionWarpPlayer.h"

namespace uking::action {

WarpPlayer::WarpPlayer(const InitArg& arg) : WarpPlayerBase(arg) {}

WarpPlayer::~WarpPlayer() = default;

bool WarpPlayer::init_(sead::Heap* heap) {
    return WarpPlayerBase::init_(heap);
}

void WarpPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    WarpPlayerBase::enter_(params);
}

void WarpPlayer::leave_() {
    WarpPlayerBase::leave_();
}

void WarpPlayer::loadParams_() {
    WarpPlayerBase::loadParams_();
    getDynamicParam(&mWarpDestMapName_d, "WarpDestMapName");
    getDynamicParam(&mWarpDestPosName_d, "WarpDestPosName");
}

void WarpPlayer::calc_() {
    WarpPlayerBase::calc_();
}

}  // namespace uking::action
