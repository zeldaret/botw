#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AwarenessShareOnePartsASPlay : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(AwarenessShareOnePartsASPlay, OnetimeStopASPlay)
public:
    explicit AwarenessShareOnePartsASPlay(const InitArg& arg);
    ~AwarenessShareOnePartsASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    sead::SafeString mPartsKey_s{};
};

}  // namespace uking::action
