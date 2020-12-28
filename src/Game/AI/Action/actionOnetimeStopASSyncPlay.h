#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OnetimeStopASSyncPlay : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(OnetimeStopASSyncPlay, OnetimeStopASPlay)
public:
    explicit OnetimeStopASSyncPlay(const InitArg& arg);
    ~OnetimeStopASSyncPlay() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x48
    const int* mSyncASSlot_s{};
    // static_param at offset 0x50
    const int* mSyncASSequenceBank_s{};
    // static_param at offset 0x58
    sead::SafeString mSyncASName_s{};
};

}  // namespace uking::action
