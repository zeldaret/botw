#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CapturedActorReactionChemical : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CapturedActorReactionChemical, ksys::act::ai::Ai)
public:
    explicit CapturedActorReactionChemical(const InitArg& arg);
    ~CapturedActorReactionChemical() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mOnEnterOnly_s{};
};

}  // namespace uking::ai
