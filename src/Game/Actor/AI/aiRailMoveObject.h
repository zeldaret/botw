#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RailMoveObject : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RailMoveObject, ksys::act::ai::Ai)
public:
    explicit RailMoveObject(const InitArg& arg);
    ~RailMoveObject() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    sead::SafeString mASKeyName_On_s{};
    // static_param at offset 0x48
    sead::SafeString mASKeyName_Off_s{};
    // map_unit_param at offset 0x58
    const float* mRailMoveSpeed_m{};
};

}  // namespace uking::ai
