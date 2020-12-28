#pragma once

#include "Game/AI/Action/actionFreeze.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MimicFreeze : public Freeze {
    SEAD_RTTI_OVERRIDE(MimicFreeze, Freeze)
public:
    explicit MimicFreeze(const InitArg& arg);
    ~MimicFreeze() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
