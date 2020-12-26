#include "Game/AI/Action/actionShutterCloseWait.h"

namespace uking::action {

ShutterCloseWait::ShutterCloseWait(const InitArg& arg) : ActionEx(arg) {}

ShutterCloseWait::~ShutterCloseWait() = default;

bool ShutterCloseWait::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void ShutterCloseWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void ShutterCloseWait::leave_() {
    ActionEx::leave_();
}

void ShutterCloseWait::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
}

void ShutterCloseWait::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
