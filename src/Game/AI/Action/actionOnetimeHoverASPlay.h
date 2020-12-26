#pragma once

#include "Game/AI/Action/actionHoverBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OnetimeHoverASPlay : public HoverBase {
    SEAD_RTTI_OVERRIDE(OnetimeHoverASPlay, HoverBase)
public:
    explicit OnetimeHoverASPlay(const InitArg& arg);
    ~OnetimeHoverASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x40
    const bool* mIsIgnoreSameAS_s{};
    // static_param at offset 0x48
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
