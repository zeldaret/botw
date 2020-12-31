#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InvincibleHiddenOctarock : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(InvincibleHiddenOctarock, ksys::act::ai::Ai)
public:
    explicit InvincibleHiddenOctarock(const InitArg& arg);
    ~InvincibleHiddenOctarock() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
