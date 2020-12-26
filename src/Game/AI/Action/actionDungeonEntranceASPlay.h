#pragma once

#include "Game/AI/Action/actionNullASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DungeonEntranceASPlay : public NullASPlay {
    SEAD_RTTI_OVERRIDE(DungeonEntranceASPlay, NullASPlay)
public:
    explicit DungeonEntranceASPlay(const InitArg& arg);
    ~DungeonEntranceASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    sead::SafeString mSetDgnName_s{};
};

}  // namespace uking::action
