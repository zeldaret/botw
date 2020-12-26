#include "Game/AI/Action/actionSandwichDetectionAreaTag.h"

namespace uking::action {

SandwichDetectionAreaTag::SandwichDetectionAreaTag(const InitArg& arg) : AreaTagAction(arg) {}

SandwichDetectionAreaTag::~SandwichDetectionAreaTag() = default;

bool SandwichDetectionAreaTag::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void SandwichDetectionAreaTag::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void SandwichDetectionAreaTag::leave_() {
    AreaTagAction::leave_();
}

void SandwichDetectionAreaTag::loadParams_() {}

void SandwichDetectionAreaTag::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
