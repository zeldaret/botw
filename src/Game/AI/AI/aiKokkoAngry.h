#pragma once

#include "Game/AI/AI/aiCreateActorWithTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KokkoAngry : public CreateActorWithTarget {
    SEAD_RTTI_OVERRIDE(KokkoAngry, CreateActorWithTarget)
public:
    explicit KokkoAngry(const InitArg& arg);
    ~KokkoAngry() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
