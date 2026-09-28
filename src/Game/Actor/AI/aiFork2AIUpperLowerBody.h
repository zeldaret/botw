#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/aiForkAI.h"

namespace uking::ai {

class Fork2AIUpperLowerBody : public ksys::act::ai::ForkAI {
    SEAD_RTTI_OVERRIDE(Fork2AIUpperLowerBody, ksys::act::ai::ForkAI)
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
