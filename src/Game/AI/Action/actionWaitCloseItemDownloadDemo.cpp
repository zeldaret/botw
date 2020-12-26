#include "Game/AI/Action/actionWaitCloseItemDownloadDemo.h"

namespace uking::action {

WaitCloseItemDownloadDemo::WaitCloseItemDownloadDemo(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WaitCloseItemDownloadDemo::~WaitCloseItemDownloadDemo() = default;

bool WaitCloseItemDownloadDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitCloseItemDownloadDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitCloseItemDownloadDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitCloseItemDownloadDemo::loadParams_() {}

void WaitCloseItemDownloadDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
