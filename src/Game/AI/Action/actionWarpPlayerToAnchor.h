#pragma once

#include "Game/AI/Action/actionWarpPlayerBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpPlayerToAnchor : public WarpPlayerBase {
    SEAD_RTTI_OVERRIDE(WarpPlayerToAnchor, WarpPlayerBase)
public:
    explicit WarpPlayerToAnchor(const InitArg& arg);
    ~WarpPlayerToAnchor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x60
    sead::SafeString mUniqueName_d{};
    // dynamic_param at offset 0x70
    sead::SafeString mAnchorName_d{};
};

}  // namespace uking::action
