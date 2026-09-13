#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FldObjDlcHeroMapRelief : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FldObjDlcHeroMapRelief, ksys::act::ai::Ai)
public:
    explicit FldObjDlcHeroMapRelief(const InitArg& arg);
    ~FldObjDlcHeroMapRelief() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    sead::SafeString mOpenFlag_m{};
    // map_unit_param at offset 0x48
    sead::SafeString mClearFlag_m{};
};

}  // namespace uking::ai
