#include "Game/Actor/Action/actionWaitOnObj.h"

namespace uking::action {

WaitOnObj::WaitOnObj(const InitArg& arg) : StopOnObj(arg) {}

WaitOnObj::~WaitOnObj() = default;

bool WaitOnObj::init_(sead::Heap* heap) {
    return StopOnObj::init_(heap);
}

void WaitOnObj::enter_(ksys::act::ai::InlineParamPack* params) {
    StopOnObj::enter_(params);
}

void WaitOnObj::leave_() {
    StopOnObj::leave_();
}

void WaitOnObj::loadParams_() {
    StopOnObj::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
    getStaticParam(&mASName_s, "ASName");
}

void WaitOnObj::calc_() {
    StopOnObj::calc_();
}

}  // namespace uking::action
