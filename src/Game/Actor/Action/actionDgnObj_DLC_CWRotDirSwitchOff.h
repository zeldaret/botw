#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DgnObj_DLC_CWRotDirSwitchOff : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DgnObj_DLC_CWRotDirSwitchOff, ksys::act::ai::Action)
public:
    explicit DgnObj_DLC_CWRotDirSwitchOff(const InitArg& arg);
    ~DgnObj_DLC_CWRotDirSwitchOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
