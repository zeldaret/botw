#pragma once

#include "Game/AI/AI/aiHorseRiddenByNPCBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRiddenByNPC : public HorseRiddenByNPCBase {
    SEAD_RTTI_OVERRIDE(HorseRiddenByNPC, HorseRiddenByNPCBase)
public:
    explicit HorseRiddenByNPC(const InitArg& arg);
    ~HorseRiddenByNPC() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x48
    const float* mNavMeshCharacterScaleAtPrecise_s{};
};

}  // namespace uking::ai
