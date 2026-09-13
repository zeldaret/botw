#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AirOctaWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AirOctaWait, ksys::act::ai::Ai)
public:
    explicit AirOctaWait(const InitArg& arg);
    ~AirOctaWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    bool* mIsSameChange_d{};
    // aitree_variable at offset 0x40
    void* mAirOctaDataMgr_a{};
};

}  // namespace uking::ai
