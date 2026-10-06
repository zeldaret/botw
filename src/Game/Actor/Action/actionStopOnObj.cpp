#include "Game/Actor/Action/actionStopOnObj.h"

namespace uking::action {

StopOnObj::StopOnObj(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StopOnObj::~StopOnObj() = default;

bool StopOnObj::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StopOnObj::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StopOnObj::leave_() {
    ksys::act::ai::Action::leave_();
}

void StopOnObj::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
}

void StopOnObj::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
