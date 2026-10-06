#pragma once

#include "Game/Actor/AI/aiNewRangeSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MagneGrabbedPartsRangeSelector : public NewRangeSelect {
    SEAD_RTTI_OVERRIDE(MagneGrabbedPartsRangeSelector, NewRangeSelect)
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
