#pragma once

#include "Game/AI/Action/actionHoverBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Hover : public HoverBase {
    SEAD_RTTI_OVERRIDE(Hover, HoverBase)
public:
    explicit Hover(const InitArg& arg);
    ~Hover() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x40
    const int* mTime_s{};
    // static_param at offset 0x48
    const int* mTimeRand_s{};
    // static_param at offset 0x50
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
