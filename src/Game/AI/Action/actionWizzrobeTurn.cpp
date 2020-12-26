#include "Game/AI/Action/actionWizzrobeTurn.h"

namespace uking::action {

WizzrobeTurn::WizzrobeTurn(const InitArg& arg) : HoverTurn(arg) {}

WizzrobeTurn::~WizzrobeTurn() = default;

bool WizzrobeTurn::init_(sead::Heap* heap) {
    return HoverTurn::init_(heap);
}

void WizzrobeTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    HoverTurn::enter_(params);
}

void WizzrobeTurn::leave_() {
    HoverTurn::leave_();
}

void WizzrobeTurn::loadParams_() {
    HoverTurn::loadParams_();
    getStaticParam(&mIsWaitASFinish_s, "IsWaitASFinish");
    getStaticParam(&mSucEndWithASFinish_s, "SucEndWithASFinish");
}

void WizzrobeTurn::calc_() {
    HoverTurn::calc_();
}

}  // namespace uking::action
