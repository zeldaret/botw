#pragma once

#include "Game/AI/Action/actionSiteBossLswordAtkWithChemical.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossLswordWhirlSlash : public SiteBossLswordAtkWithChemical {
    SEAD_RTTI_OVERRIDE(SiteBossLswordWhirlSlash, SiteBossLswordAtkWithChemical)
public:
    explicit SiteBossLswordWhirlSlash(const InitArg& arg);
    ~SiteBossLswordWhirlSlash() override;

    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x1e8
    const float* mEmitChangeDist_s{};
    // static_param at offset 0x1f0
    const float* mCircleEmitOffset_s{};
};

}  // namespace uking::action
