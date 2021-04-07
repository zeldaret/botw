#pragma once

#include "Game/AI/AI/aiForkAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class Fork2AIUpperLowerBody : public ForkAI {
    SEAD_RTTI_OVERRIDE(Fork2AIUpperLowerBody, ForkAI)
public:
    explicit Fork2AIUpperLowerBody(const InitArg& arg);
    ~Fork2AIUpperLowerBody() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
