#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerCamera : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerCamera, ksys::act::ai::Ai)
public:
    explicit PlayerCamera(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
};

}  // namespace uking::ai
