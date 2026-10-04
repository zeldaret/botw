#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCSurprised : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCSurprised, ksys::act::ai::Ai)
public:
    explicit NPCSurprised(const InitArg& arg);
    ~NPCSurprised() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    int* mTerrorLayer_d{};
    // dynamic_param at offset 0x40
    bool* mIsNeedUnEquipWeapon_d{};
    // dynamic_param at offset 0x48
    ksys::act::BaseProcLink* mTerrorEmitter_d{};
};

}  // namespace uking::ai
