#include "Game/AI/Action/actionChangeEmotion.h"

namespace uking::action {

ChangeEmotion::ChangeEmotion(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeEmotion::~ChangeEmotion() = default;

bool ChangeEmotion::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeEmotion::loadParams_() {
    getDynamicParam(&mIsOnlyFace_d, "IsOnlyFace");
    getDynamicParam(&mEmotionType_d, "EmotionType");
}

}  // namespace uking::action
