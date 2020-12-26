#pragma once

#include "Game/AI/Action/actionForbidTag.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DRCAppNoUseTag : public ForbidTag {
    SEAD_RTTI_OVERRIDE(DRCAppNoUseTag, ForbidTag)
public:
    explicit DRCAppNoUseTag(const InitArg& arg);
    ~DRCAppNoUseTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const int* mDRCAppNoUseCause_m{};
};

}  // namespace uking::action
