#pragma once

#include "Game/AI/AI/aiSimpleLiftable.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BarrelBomb : public SimpleLiftable {
    SEAD_RTTI_OVERRIDE(BarrelBomb, SimpleLiftable)
public:
    explicit BarrelBomb(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0xc8
    const bool* mIsFixedPlace_m{};
};

}  // namespace uking::ai
