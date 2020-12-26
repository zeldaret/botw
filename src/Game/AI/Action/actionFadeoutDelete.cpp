#include "Game/AI/Action/actionFadeoutDelete.h"

namespace uking::action {

FadeoutDelete::FadeoutDelete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FadeoutDelete::~FadeoutDelete() = default;

bool FadeoutDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FadeoutDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FadeoutDelete::leave_() {
    ksys::act::ai::Action::leave_();
}

void FadeoutDelete::loadParams_() {
    getStaticParam(&mFadeoutTime_s, "FadeoutTime");
    getStaticParam(&mDeleteType_s, "DeleteType");
}

void FadeoutDelete::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
