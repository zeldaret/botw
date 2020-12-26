#include "Game/AI/Action/actionShutterClose.h"

namespace uking::action {

ShutterClose::ShutterClose(const InitArg& arg) : ActionEx(arg) {}

ShutterClose::~ShutterClose() = default;

bool ShutterClose::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void ShutterClose::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void ShutterClose::leave_() {
    ActionEx::leave_();
}

void ShutterClose::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getMapUnitParam(&mMoveAxis_m, "MoveAxis");
    getMapUnitParam(&mMoveDis_m, "MoveDis");
    getMapUnitParam(&mMoveSpeed_m, "MoveSpeed");
}

void ShutterClose::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
