#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CopyMapPinPosition : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CopyMapPinPosition, ksys::act::ai::Action)
public:
    explicit CopyMapPinPosition(const InitArg& arg);
    ~CopyMapPinPosition() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mPinColorIdx_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mGameDataVec3_d{};
};

}  // namespace uking::action
