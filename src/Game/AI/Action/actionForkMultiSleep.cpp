#include "Game/AI/Action/actionForkMultiSleep.h"

namespace uking::action {

ForkMultiSleep::ForkMultiSleep(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkMultiSleep::~ForkMultiSleep() = default;

bool ForkMultiSleep::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkMultiSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkMultiSleep::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkMultiSleep::loadParams_() {
    getStaticParam(&mNum_s, "Num");
    getStaticParam(&mPartsBaseName_s, "PartsBaseName");
}

void ForkMultiSleep::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
