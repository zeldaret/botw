#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CookPotRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CookPotRoot, ksys::act::ai::Ai)
public:
    explicit CookPotRoot(const InitArg& arg);
    ~CookPotRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mInitBurnState_m{};
    // aitree_variable at offset 0x40
    void* mCurrentCookResultHolder_a{};
};

}  // namespace uking::ai
