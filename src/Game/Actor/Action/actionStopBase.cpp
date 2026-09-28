#include "Game/Actor/Action/actionStopBase.h"

namespace uking::action {

StopBase::StopBase(const InitArg& arg) : ActionEx(arg) {}

void StopBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void StopBase::leave_() {
    ActionEx::leave_();
}

void StopBase::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
}

void StopBase::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
