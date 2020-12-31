#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HasPreActorSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HasPreActorSelect, ksys::act::ai::Ai)
public:
    explicit HasPreActorSelect(const InitArg& arg);
    ~HasPreActorSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
