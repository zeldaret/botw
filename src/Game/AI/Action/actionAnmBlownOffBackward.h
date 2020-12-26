#pragma once

#include "Game/AI/Action/actionAnmBlownOff.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnmBlownOffBackward : public AnmBlownOff {
    SEAD_RTTI_OVERRIDE(AnmBlownOffBackward, AnmBlownOff)
public:
    explicit AnmBlownOffBackward(const InitArg& arg);
    ~AnmBlownOffBackward() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
