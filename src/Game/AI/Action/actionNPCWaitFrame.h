#pragma once

#include "Game/AI/Action/actionNPCWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCWaitFrame : public NPCWait {
    SEAD_RTTI_OVERRIDE(NPCWaitFrame, NPCWait)
public:
    explicit NPCWaitFrame(const InitArg& arg);
    ~NPCWaitFrame() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const int* mWaitFrame_s{};
};

}  // namespace uking::action
