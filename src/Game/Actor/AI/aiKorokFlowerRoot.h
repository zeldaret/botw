#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KorokFlowerRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KorokFlowerRoot, ksys::act::ai::Ai)
public:
    explicit KorokFlowerRoot(const InitArg& arg);
    ~KorokFlowerRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const bool* mIsNoAppearEffect_m{};
    // map_unit_param at offset 0x40
    const bool* mIsLastKorokFlower_m{};
};

}  // namespace uking::ai
