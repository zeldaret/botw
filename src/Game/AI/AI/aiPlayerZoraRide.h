#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerZoraRide : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerZoraRide, ksys::act::ai::Ai)
public:
    explicit PlayerZoraRide(const InitArg& arg);
    ~PlayerZoraRide() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
