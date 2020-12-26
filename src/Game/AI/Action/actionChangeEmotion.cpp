#include "Game/AI/Action/actionChangeEmotion.h"

namespace uking::action {

ChangeEmotion::ChangeEmotion(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeEmotion::~ChangeEmotion() = default;

bool ChangeEmotion::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeEmotion::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChangeEmotion::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChangeEmotion::loadParams_() {
    getDynamicParam(&mIsOnlyFace_d, "IsOnlyFace");
    getDynamicParam(&mEmotionType_d, "EmotionType");
}

void ChangeEmotion::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
