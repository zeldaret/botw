#pragma once

#include "Game/AI/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SlideMoveViewTarget : public MoveBase {
    SEAD_RTTI_OVERRIDE(SlideMoveViewTarget, MoveBase)
public:
    explicit SlideMoveViewTarget(const InitArg& arg);
    ~SlideMoveViewTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xe0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
