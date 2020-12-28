#include "Game/AI/Action/actionFall.h"

namespace uking::action {

Fall::Fall(const InitArg& arg) : ActionEx(arg) {}

Fall::~Fall() = default;

void Fall::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void Fall::leave_() {
    ActionEx::leave_();
}

void Fall::loadParams_() {
    getStaticParam(&mInWaterDepth_s, "InWaterDepth");
    getStaticParam(&mASName_s, "ASName");
}

void Fall::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
