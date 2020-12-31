#include "Game/AI/AI/aiWarpActivateTerminal.h"

namespace uking::ai {

WarpActivateTerminal::WarpActivateTerminal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WarpActivateTerminal::~WarpActivateTerminal() = default;

bool WarpActivateTerminal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WarpActivateTerminal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WarpActivateTerminal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WarpActivateTerminal::loadParams_() {
    getStaticParam(&mDoLimitAngle_s, "DoLimitAngle");
    getStaticParam(&mIsAbleToReboot_s, "IsAbleToReboot");
    getStaticParam(&mIsCheckLimit_s, "IsCheckLimit");
    getStaticParam(&mIsRejectMsgForRemains_s, "IsRejectMsgForRemains");
    getMapUnitParam(&mRemainsTerminalType_m, "RemainsTerminalType");
    getMapUnitParam(&mRemainsTerminalIndex_m, "RemainsTerminalIndex");
}

}  // namespace uking::ai
