#include "Game/Actor/Action/actionSandwichDetectionAreaTag.h"

namespace uking::action {

SandwichDetectionAreaTag::SandwichDetectionAreaTag(const InitArg& arg) : AreaActionBase(arg) {}

SandwichDetectionAreaTag::~SandwichDetectionAreaTag() = default;

bool SandwichDetectionAreaTag::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

void SandwichDetectionAreaTag::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
}

void SandwichDetectionAreaTag::leave_() {
    AreaActionBase::leave_();
}

void SandwichDetectionAreaTag::loadParams_() {}

void SandwichDetectionAreaTag::calc_() {
    AreaActionBase::calc_();
}

}  // namespace uking::action
