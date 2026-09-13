#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DgnObj_DLC_CWRotDirSwitch : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DgnObj_DLC_CWRotDirSwitch, ksys::act::ai::Ai)
public:
    explicit DgnObj_DLC_CWRotDirSwitch(const InitArg& arg);
    ~DgnObj_DLC_CWRotDirSwitch() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
