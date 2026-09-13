#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RailMoveObjectOneWay : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RailMoveObjectOneWay, ksys::act::ai::Ai)
public:
    explicit RailMoveObjectOneWay(const InitArg& arg);
    ~RailMoveObjectOneWay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    sead::SafeString mASKeyName_On_s{};
    // static_param at offset 0x48
    sead::SafeString mASKeyName_Off_s{};
};

}  // namespace uking::ai
