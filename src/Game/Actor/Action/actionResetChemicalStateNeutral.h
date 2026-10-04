#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ResetChemicalStateNeutral : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ResetChemicalStateNeutral, ksys::act::ai::Action)
public:
    explicit ResetChemicalStateNeutral(const InitArg& arg);
    ~ResetChemicalStateNeutral() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
