#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DamageTypeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DamageTypeSelect, ksys::act::ai::Ai)
public:
    explicit DamageTypeSelect(const InitArg& arg);
    ~DamageTypeSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mDamageType_s{};
};

}  // namespace uking::ai
