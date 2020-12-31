#pragma once

#include "Game/AI/AI/aiAddCarried.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BeamosCarried : public AddCarried {
    SEAD_RTTI_OVERRIDE(BeamosCarried, AddCarried)
public:
    explicit BeamosCarried(const InitArg& arg);
    ~BeamosCarried() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x160
    void* mBeamActorLink_a{};
};

}  // namespace uking::ai
