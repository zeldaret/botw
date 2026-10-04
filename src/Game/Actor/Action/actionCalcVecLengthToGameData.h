#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CalcVecLengthToGameData : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CalcVecLengthToGameData, ksys::act::ai::Action)
public:
    explicit CalcVecLengthToGameData(const InitArg& arg);
    ~CalcVecLengthToGameData() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mCalcY_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mGameDataVec3fSrcName_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mGameDataFloatToName_d{};
};

}  // namespace uking::action
