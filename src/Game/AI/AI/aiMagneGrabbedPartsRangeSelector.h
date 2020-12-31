#pragma once

#include "Game/AI/AI/aiRangeSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MagneGrabbedPartsRangeSelector : public RangeSelect {
    SEAD_RTTI_OVERRIDE(MagneGrabbedPartsRangeSelector, RangeSelect)
public:
    explicit MagneGrabbedPartsRangeSelector(const InitArg& arg);
    ~MagneGrabbedPartsRangeSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x50
    sead::SafeString mPartsName_s{};
};

}  // namespace uking::ai
