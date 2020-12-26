#pragma once

#include "Game/AI/Action/actionChangeSceneBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FromCDungeonToMainField : public ChangeSceneBase {
    SEAD_RTTI_OVERRIDE(FromCDungeonToMainField, ChangeSceneBase)
public:
    explicit FromCDungeonToMainField(const InitArg& arg);
    ~FromCDungeonToMainField() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
