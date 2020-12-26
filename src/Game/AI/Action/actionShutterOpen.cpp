#include "Game/AI/Action/actionShutterOpen.h"

namespace uking::action {

ShutterOpen::ShutterOpen(const InitArg& arg) : ActionEx(arg) {}

ShutterOpen::~ShutterOpen() = default;

bool ShutterOpen::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void ShutterOpen::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void ShutterOpen::leave_() {
    ActionEx::leave_();
}

void ShutterOpen::loadParams_() {
    getStaticParam(&mOnLink_s, "OnLink");
    getStaticParam(&mIsPreOpen_s, "IsPreOpen");
    getStaticParam(&mASName_s, "ASName");
    getMapUnitParam(&mMoveAxis_m, "MoveAxis");
    getMapUnitParam(&mMoveDis_m, "MoveDis");
    getMapUnitParam(&mMoveSpeed_m, "MoveSpeed");
}

void ShutterOpen::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
