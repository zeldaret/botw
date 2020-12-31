#pragma once

#include "Game/AI/AI/aiSimpleLiftable.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OctarockOptionRoot : public SimpleLiftable {
    SEAD_RTTI_OVERRIDE(OctarockOptionRoot, SimpleLiftable)
public:
    explicit OctarockOptionRoot(const InitArg& arg);
    ~OctarockOptionRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xc8
    const bool* mIsBreakable_s{};
    // static_param at offset 0xd0
    const bool* mIsMimicry_s{};
};

}  // namespace uking::ai
