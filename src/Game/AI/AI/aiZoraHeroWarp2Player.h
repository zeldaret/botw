#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ZoraHeroWarp2Player : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ZoraHeroWarp2Player, ksys::act::ai::Ai)
public:
    explicit ZoraHeroWarp2Player(const InitArg& arg);
    ~ZoraHeroWarp2Player() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mDepthOffset_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
