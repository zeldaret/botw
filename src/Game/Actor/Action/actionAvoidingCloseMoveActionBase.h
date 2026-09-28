#pragma once

#include "Game/Actor/Action/actionAvoidingCloseMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AvoidingCloseMoveActionBase : public AvoidingCloseMoveBase {
    SEAD_RTTI_OVERRIDE(AvoidingCloseMoveActionBase, AvoidingCloseMoveBase)
public:
    explicit AvoidingCloseMoveActionBase(const InitArg& arg);
    ~AvoidingCloseMoveActionBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
