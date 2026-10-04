#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PreyChemicalDeadReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PreyChemicalDeadReaction, ksys::act::ai::Ai)
public:
    explicit PreyChemicalDeadReaction(const InitArg& arg);
    ~PreyChemicalDeadReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
