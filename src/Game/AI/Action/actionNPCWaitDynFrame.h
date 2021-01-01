#pragma once

#include "Game/AI/Action/actionNPCWaitFrame.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCWaitDynFrame : public NPCWaitFrame {
    SEAD_RTTI_OVERRIDE(NPCWaitDynFrame, NPCWaitFrame)
public:
    explicit NPCWaitDynFrame(const InitArg& arg);
    ~NPCWaitDynFrame() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x58
    int* mDynWaitFrame_d{};
    // dynamic_param at offset 0x60
    sead::SafeString mDynASName_d{};
};

}  // namespace uking::action
