#pragma once

#include "Game/AI/Action/actionSwimMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimMoveOneTimeAS : public SwimMoveBase {
    SEAD_RTTI_OVERRIDE(SwimMoveOneTimeAS, SwimMoveBase)
public:
    explicit SwimMoveOneTimeAS(const InitArg& arg);
    ~SwimMoveOneTimeAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xe8
    const bool* mIsIgnoreSameKey_s{};
    // static_param at offset 0xf0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
