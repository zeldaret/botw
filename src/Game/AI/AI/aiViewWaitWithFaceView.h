#pragma once

#include "Game/AI/AI/aiViewWait.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ViewWaitWithFaceView : public ViewWait {
    SEAD_RTTI_OVERRIDE(ViewWaitWithFaceView, ViewWait)
public:
    explicit ViewWaitWithFaceView(const InitArg& arg);
    ~ViewWaitWithFaceView() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x60
    const bool* mUseSimpleOffset_s{};
};

}  // namespace uking::ai
