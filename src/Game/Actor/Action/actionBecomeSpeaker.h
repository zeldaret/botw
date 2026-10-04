#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BecomeSpeaker : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BecomeSpeaker, ksys::act::ai::Action)
public:
    explicit BecomeSpeaker(const InitArg& arg);
    ~BecomeSpeaker() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
