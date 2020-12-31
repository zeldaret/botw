#pragma once

#include "Game/AI/AI/aiSimpleLiftable.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AncientNecklaceBallBase : public SimpleLiftable {
    SEAD_RTTI_OVERRIDE(AncientNecklaceBallBase, SimpleLiftable)
public:
    explicit AncientNecklaceBallBase(const InitArg& arg);
    ~AncientNecklaceBallBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xc8
    const bool* mIsIgnoreSameOnAS_s{};
    // static_param at offset 0xd0
    const bool* mIsIgnoreSameOffAS_s{};
    // static_param at offset 0xd8
    sead::SafeString mOnAS_s{};
    // static_param at offset 0xe8
    sead::SafeString mOffAS_s{};
};

}  // namespace uking::ai
