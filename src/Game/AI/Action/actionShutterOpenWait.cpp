#include "Game/AI/Action/actionShutterOpenWait.h"

namespace uking::action {

ShutterOpenWait::ShutterOpenWait(const InitArg& arg) : ActionEx(arg) {}

ShutterOpenWait::~ShutterOpenWait() = default;

bool ShutterOpenWait::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void ShutterOpenWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void ShutterOpenWait::leave_() {
    ActionEx::leave_();
}

void ShutterOpenWait::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getMapUnitParam(&mMoveAxis_m, "MoveAxis");
    getMapUnitParam(&mMoveDis_m, "MoveDis");
}

void ShutterOpenWait::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
