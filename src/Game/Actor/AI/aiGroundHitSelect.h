#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GroundHitSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GroundHitSelect, ksys::act::ai::Ai)
public:
    explicit GroundHitSelect(const InitArg& arg);
    ~GroundHitSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsActionEndEnd_s{};
    // static_param at offset 0x40
    const bool* mIsEnterCheck_s{};
};

}  // namespace uking::ai
