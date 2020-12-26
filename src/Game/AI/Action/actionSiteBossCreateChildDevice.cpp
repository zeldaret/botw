#include "Game/AI/Action/actionSiteBossCreateChildDevice.h"

namespace uking::action {

SiteBossCreateChildDevice::SiteBossCreateChildDevice(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossCreateChildDevice::~SiteBossCreateChildDevice() = default;

bool SiteBossCreateChildDevice::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossCreateChildDevice::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossCreateChildDevice::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossCreateChildDevice::loadParams_() {
    getDynamicParam(&mIsCreateA_d, "IsCreateA");
    getDynamicParam(&mIsCreateB_d, "IsCreateB");
    getDynamicParam(&mIsCreateC_d, "IsCreateC");
    getDynamicParam(&mIsCreateD_d, "IsCreateD");
}

void SiteBossCreateChildDevice::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
