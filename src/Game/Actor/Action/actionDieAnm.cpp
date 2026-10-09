#include "Game/Actor/Action/actionDieAnm.h"

namespace uking::action {

DieAnm::DieAnm(const InitArg& arg) : StopBase(arg) {}

DieAnm::~DieAnm() = default;

bool DieAnm::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void DieAnm::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void DieAnm::leave_() {
    StopBase::leave_();
}

void DieAnm::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void DieAnm::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
