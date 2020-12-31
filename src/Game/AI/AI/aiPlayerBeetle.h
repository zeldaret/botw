#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerBeetle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerBeetle, ksys::act::ai::Ai)
public:
    explicit PlayerBeetle(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
};

}  // namespace uking::ai
