#include "Game/Actor/Action/actionSandwichDetectionAreaTagSimple.h"

namespace uking::action {

SandwichDetectionAreaTagSimple::SandwichDetectionAreaTagSimple(const InitArg& arg)
    : AreaActionBase(arg) {}

SandwichDetectionAreaTagSimple::~SandwichDetectionAreaTagSimple() = default;

bool SandwichDetectionAreaTagSimple::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

void SandwichDetectionAreaTagSimple::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
}

void SandwichDetectionAreaTagSimple::leave_() {
    AreaActionBase::leave_();
}

void SandwichDetectionAreaTagSimple::loadParams_() {}

void SandwichDetectionAreaTagSimple::calc_() {
    AreaActionBase::calc_();
}

}  // namespace uking::action
