#pragma once

#include "Game/AI/Action/actionForkASPlayBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASPlay : public ForkASPlayBase {
    SEAD_RTTI_OVERRIDE(ForkASPlay, ForkASPlayBase)
public:
    explicit ForkASPlay(const InitArg& arg);
    ~ForkASPlay() override;

    void loadParams_() override;

protected:
    // static_param at offset 0x50
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
