#pragma once

#include "Game/AI/AI/aiDgnObj_DLC_CogWheel2.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DgnObj_DLC_CW_WithEntityBody00 : public DgnObj_DLC_CogWheel2 {
    SEAD_RTTI_OVERRIDE(DgnObj_DLC_CW_WithEntityBody00, DgnObj_DLC_CogWheel2)
public:
    explicit DgnObj_DLC_CW_WithEntityBody00(const InitArg& arg);
    ~DgnObj_DLC_CW_WithEntityBody00() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
