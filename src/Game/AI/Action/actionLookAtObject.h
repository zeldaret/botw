#pragma once

#include "Game/AI/Action/actionLookAtObjectBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LookAtObject : public LookAtObjectBase {
    SEAD_RTTI_OVERRIDE(LookAtObject, LookAtObjectBase)
public:
    explicit LookAtObject(const InitArg& arg);
    ~LookAtObject() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
