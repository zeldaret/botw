#pragma once

#include "Game/AI/AI/aiSimpleLiftable.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FixableLiftable : public SimpleLiftable {
    SEAD_RTTI_OVERRIDE(FixableLiftable, SimpleLiftable)
public:
    explicit FixableLiftable(const InitArg& arg);
    ~FixableLiftable() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xc8
    const float* mCancelFixedScale_s{};
    // map_unit_param at offset 0xd0
    const bool* mIsFixedPlace_m{};
};

}  // namespace uking::ai
