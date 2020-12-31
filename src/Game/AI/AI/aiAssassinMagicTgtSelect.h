#pragma once

#include "Game/AI/AI/aiTargetInAreaSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinMagicTgtSelect : public TargetInAreaSelect {
    SEAD_RTTI_OVERRIDE(AssassinMagicTgtSelect, TargetInAreaSelect)
public:
    explicit AssassinMagicTgtSelect(const InitArg& arg);
    ~AssassinMagicTgtSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const float* mHeight_s{};
};

}  // namespace uking::ai
