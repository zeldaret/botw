#pragma once

#include "Game/AI/Action/actionForkAlwaysTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAlwaysTurnUDLimit : public ForkAlwaysTurn {
    SEAD_RTTI_OVERRIDE(ForkAlwaysTurnUDLimit, ForkAlwaysTurn)
public:
    explicit ForkAlwaysTurnUDLimit(const InitArg& arg);
    ~ForkAlwaysTurnUDLimit() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc8
    const float* mLimitUD_s{};
};

}  // namespace uking::action
