#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class IchigekiHeartUiOpen : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(IchigekiHeartUiOpen, ksys::act::ai::Action)
public:
    explicit IchigekiHeartUiOpen(const InitArg& arg);
    ~IchigekiHeartUiOpen() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
