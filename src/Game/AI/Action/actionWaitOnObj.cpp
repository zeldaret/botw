#include "Game/AI/Action/actionWaitOnObj.h"

namespace uking::action {

WaitOnObj::WaitOnObj(const InitArg& arg) : WaitOnObjBase(arg) {}

WaitOnObj::~WaitOnObj() = default;

bool WaitOnObj::init_(sead::Heap* heap) {
    return WaitOnObjBase::init_(heap);
}

void WaitOnObj::enter_(ksys::act::ai::InlineParamPack* params) {
    WaitOnObjBase::enter_(params);
}

void WaitOnObj::leave_() {
    WaitOnObjBase::leave_();
}

void WaitOnObj::loadParams_() {
    WaitOnObjBase::loadParams_();
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mTimeRand_s, "TimeRand");
    getStaticParam(&mASName_s, "ASName");
}

void WaitOnObj::calc_() {
    WaitOnObjBase::calc_();
}

}  // namespace uking::action
