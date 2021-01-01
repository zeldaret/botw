#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChangeEmotion : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ChangeEmotion, ksys::act::ai::Action)
public:
    explicit ChangeEmotion(const InitArg& arg);
    ~ChangeEmotion() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mIsOnlyFace_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mEmotionType_d{};
};

}  // namespace uking::action
