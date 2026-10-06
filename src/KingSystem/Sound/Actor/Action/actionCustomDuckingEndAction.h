#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::snd {

class CustomDuckingEndAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CustomDuckingEndAction, ksys::act::ai::Action)
public:
    explicit CustomDuckingEndAction(const InitArg& arg);
    ~CustomDuckingEndAction() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace ksys::snd
