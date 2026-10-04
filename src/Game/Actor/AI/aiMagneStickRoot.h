#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MagneStickRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MagneStickRoot, ksys::act::ai::Ai)
public:
    explicit MagneStickRoot(const InitArg& arg);
    ~MagneStickRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x8];
    // static_param at offset 0x40
    const float* mDefaultConnectionDistance_s{};
    // static_param at offset 0x48
    const float* mCollideRadiusFactor_s{};
    // map_unit_param at offset 0x50
    const float* mCollideRadius_m{};
    // map_unit_param at offset 0x58
    const bool* mJoinSystemGroup_m{};
    // map_unit_param at offset 0x60
    const bool* mRegistFromBeginning_m{};
    // map_unit_param at offset 0x68
    const bool* mIgnoreObstacle_m{};
    // aitree_variable at offset 0x70
    bool* mIsTargetFixedAcceptor_a{};
};

}  // namespace uking::ai
