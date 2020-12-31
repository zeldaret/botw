#pragma once

#include "Game/AI/AI/aiSeqTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AirOctaBoardBurn : public SeqTwoAction {
    SEAD_RTTI_OVERRIDE(AirOctaBoardBurn, SeqTwoAction)
public:
    explicit AirOctaBoardBurn(const InitArg& arg);
    ~AirOctaBoardBurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x50
    void* mAirOctaDataMgr_a{};
};

}  // namespace uking::ai
