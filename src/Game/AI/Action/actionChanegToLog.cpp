#include "Game/AI/Action/actionChanegToLog.h"

namespace uking::action {

ChanegToLog::ChanegToLog(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChanegToLog::~ChanegToLog() = default;

bool ChanegToLog::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChanegToLog::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChanegToLog::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChanegToLog::loadParams_() {}

void ChanegToLog::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
