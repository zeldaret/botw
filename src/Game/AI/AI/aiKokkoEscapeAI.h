#pragma once

#include "Game/AI/AI/aiAnimalEscapeAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KokkoEscapeAI : public AnimalEscapeAI {
    SEAD_RTTI_OVERRIDE(KokkoEscapeAI, AnimalEscapeAI)
public:
    explicit KokkoEscapeAI(const InitArg& arg);
    ~KokkoEscapeAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
