#pragma once

#include "Game/AI/AI/aiRegistedActorNumTwoSelectBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RegistedActorNumTwoSelect : public RegistedActorNumTwoSelectBase {
    SEAD_RTTI_OVERRIDE(RegistedActorNumTwoSelect, RegistedActorNumTwoSelectBase)
public:
    explicit RegistedActorNumTwoSelect(const InitArg& arg);
    ~RegistedActorNumTwoSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const int* mNum_s{};
};

}  // namespace uking::ai
