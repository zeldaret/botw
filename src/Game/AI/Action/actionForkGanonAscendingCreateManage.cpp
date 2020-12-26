#include "Game/AI/Action/actionForkGanonAscendingCreateManage.h"

namespace uking::action {

ForkGanonAscendingCreateManage::ForkGanonAscendingCreateManage(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkGanonAscendingCreateManage::~ForkGanonAscendingCreateManage() = default;

bool ForkGanonAscendingCreateManage::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGanonAscendingCreateManage::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkGanonAscendingCreateManage::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkGanonAscendingCreateManage::loadParams_() {
    getStaticParam(&mMaxNum_s, "MaxNum");
    getStaticParam(&mCreateGrudgeName_s, "CreateGrudgeName");
}

void ForkGanonAscendingCreateManage::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
