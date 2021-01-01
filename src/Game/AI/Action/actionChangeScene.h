#pragma once

#include "Game/AI/Action/actionChangeSceneBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChangeScene : public ChangeSceneBase {
    SEAD_RTTI_OVERRIDE(ChangeScene, ChangeSceneBase)
public:
    explicit ChangeScene(const InitArg& arg);
    ~ChangeScene() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x50
    int* mFadeType_d{};
    // dynamic_param at offset 0x58
    sead::SafeString mWarpDestMapName_d{};
    // dynamic_param at offset 0x68
    sead::SafeString mWarpDestPosName_d{};
};

}  // namespace uking::action
