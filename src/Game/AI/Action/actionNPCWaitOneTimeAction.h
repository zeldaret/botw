#pragma once

#include "Game/AI/Action/actionNPCWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCWaitOneTimeAction : public NPCWait {
    SEAD_RTTI_OVERRIDE(NPCWaitOneTimeAction, NPCWait)
public:
    explicit NPCWaitOneTimeAction(const InitArg& arg);
    ~NPCWaitOneTimeAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsIgnoreSameKey_s{};
    // static_param at offset 0x28
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
