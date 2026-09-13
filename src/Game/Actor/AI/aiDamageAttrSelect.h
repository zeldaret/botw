#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DamageAttrSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DamageAttrSelect, ksys::act::ai::Ai)
public:
    explicit DamageAttrSelect(const InitArg& arg);
    ~DamageAttrSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mKeyAttribute_s{};
    // static_param at offset 0x40
    const int* mOption_s{};
};

}  // namespace uking::ai
