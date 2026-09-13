#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossAttackRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossAttackRoot, ksys::act::ai::Ai)
public:
    explicit SiteBossAttackRoot(const InitArg& arg);
    ~SiteBossAttackRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mEquipWeapon_s{};
};

}  // namespace uking::ai
