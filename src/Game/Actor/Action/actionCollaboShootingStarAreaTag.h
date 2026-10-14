#pragma once

#include "Game/Actor/Area/Action/actionAreaActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CollaboShootingStarAreaTag : public AreaActionBase {
    SEAD_RTTI_OVERRIDE(CollaboShootingStarAreaTag, AreaActionBase)
public:
    explicit CollaboShootingStarAreaTag(const InitArg& arg);
    ~CollaboShootingStarAreaTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x38
    sead::SafeString mcollaboSSFalloutFlagName_m{};
};

}  // namespace uking::action
