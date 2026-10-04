#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LastAttackerSpecialActionSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LastAttackerSpecialActionSelect, ksys::act::ai::Ai)
public:
    explicit LastAttackerSpecialActionSelect(const InitArg& arg);
    ~LastAttackerSpecialActionSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsAngerActorSpecial_s{};
};

}  // namespace uking::ai
