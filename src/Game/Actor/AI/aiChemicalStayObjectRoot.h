#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChemicalStayObjectRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ChemicalStayObjectRoot, ksys::act::ai::Ai)
public:
    explicit ChemicalStayObjectRoot(const InitArg& arg);
    ~ChemicalStayObjectRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsCheckDelete_s{};
};

}  // namespace uking::ai
