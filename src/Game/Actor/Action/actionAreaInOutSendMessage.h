#pragma once

#include "Game/Actor/Area/Action/actionAreaActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaInOutSendMessage : public AreaActionBase {
    SEAD_RTTI_OVERRIDE(AreaInOutSendMessage, AreaActionBase)
public:
    explicit AreaInOutSendMessage(const InitArg& arg);
    ~AreaInOutSendMessage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x38
    const int* mBufferNum_s{};
};

}  // namespace uking::action
