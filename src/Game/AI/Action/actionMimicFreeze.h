#pragma once

#include "Game/AI/Action/actionFreeze.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MimicFreeze : public Freeze {
    SEAD_RTTI_OVERRIDE(MimicFreeze, Freeze)
public:
    explicit MimicFreeze(const InitArg& arg);
    ~MimicFreeze() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
