#pragma once

#include "Game/AI/Action/actionWaitOnObjBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaitOnObj : public WaitOnObjBase {
    SEAD_RTTI_OVERRIDE(WaitOnObj, WaitOnObjBase)
public:
    explicit WaitOnObj(const InitArg& arg);
    ~WaitOnObj() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb8
    const int* mTime_s{};
    // static_param at offset 0xc0
    const int* mTimeRand_s{};
    // static_param at offset 0xc8
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
