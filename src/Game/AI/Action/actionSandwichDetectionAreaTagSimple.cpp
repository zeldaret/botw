#include "Game/AI/Action/actionSandwichDetectionAreaTagSimple.h"

namespace uking::action {

SandwichDetectionAreaTagSimple::SandwichDetectionAreaTagSimple(const InitArg& arg)
    : AreaTagAction(arg) {}

SandwichDetectionAreaTagSimple::~SandwichDetectionAreaTagSimple() = default;

bool SandwichDetectionAreaTagSimple::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void SandwichDetectionAreaTagSimple::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void SandwichDetectionAreaTagSimple::leave_() {
    AreaTagAction::leave_();
}

void SandwichDetectionAreaTagSimple::loadParams_() {}

void SandwichDetectionAreaTagSimple::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
