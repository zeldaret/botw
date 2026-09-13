#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NearCreateSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NearCreateSelect, ksys::act::ai::Ai)
public:
    explicit NearCreateSelect(const InitArg& arg);
    ~NearCreateSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mIsNearCreate_m{};
};

}  // namespace uking::ai
