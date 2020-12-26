#include "Game/AI/Action/actionTeachPlayerInAreaForRefActor.h"

namespace uking::action {

TeachPlayerInAreaForRefActor::TeachPlayerInAreaForRefActor(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

TeachPlayerInAreaForRefActor::~TeachPlayerInAreaForRefActor() = default;

bool TeachPlayerInAreaForRefActor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TeachPlayerInAreaForRefActor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void TeachPlayerInAreaForRefActor::leave_() {
    ksys::act::ai::Action::leave_();
}

void TeachPlayerInAreaForRefActor::loadParams_() {
    getStaticParam(&mNextTimer_s, "NextTimer");
}

void TeachPlayerInAreaForRefActor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
