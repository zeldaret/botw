#include "Game/AI/Action/actionExplodeReserved.h"

namespace uking::action {

ExplodeReserved::ExplodeReserved(const InitArg& arg) : StopASPlay(arg) {}

ExplodeReserved::~ExplodeReserved() = default;

bool ExplodeReserved::init_(sead::Heap* heap) {
    return StopASPlay::init_(heap);
}

void ExplodeReserved::enter_(ksys::act::ai::InlineParamPack* params) {
    StopASPlay::enter_(params);
}

void ExplodeReserved::leave_() {
    StopASPlay::leave_();
}

void ExplodeReserved::loadParams_() {
    StopASPlay::loadParams_();
}

void ExplodeReserved::calc_() {
    StopASPlay::calc_();
}

}  // namespace uking::action
