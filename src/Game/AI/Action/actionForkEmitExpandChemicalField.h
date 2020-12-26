#pragma once

#include "Game/AI/Action/actionForkEmitExpandField.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkEmitExpandChemicalField : public ForkEmitExpandField {
    SEAD_RTTI_OVERRIDE(ForkEmitExpandChemicalField, ForkEmitExpandField)
public:
    explicit ForkEmitExpandChemicalField(const InitArg& arg);
    ~ForkEmitExpandChemicalField() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
