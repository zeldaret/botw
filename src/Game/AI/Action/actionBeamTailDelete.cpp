#include "Game/AI/Action/actionBeamTailDelete.h"

namespace uking::action {

BeamTailDelete::BeamTailDelete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BeamTailDelete::~BeamTailDelete() = default;

bool BeamTailDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BeamTailDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BeamTailDelete::leave_() {
    ksys::act::ai::Action::leave_();
}

void BeamTailDelete::loadParams_() {}

void BeamTailDelete::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
