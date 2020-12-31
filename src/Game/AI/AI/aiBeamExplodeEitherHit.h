#pragma once

#include "Game/AI/AI/aiBeamExplode.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BeamExplodeEitherHit : public BeamExplode {
    SEAD_RTTI_OVERRIDE(BeamExplodeEitherHit, BeamExplode)
public:
    explicit BeamExplodeEitherHit(const InitArg& arg);
    ~BeamExplodeEitherHit() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x58
    bool* mIsReflectThrownBullet_a{};
};

}  // namespace uking::ai
