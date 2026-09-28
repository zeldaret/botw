#pragma once

#include "Game/Actor/Action/actionDisappearAndEscapeBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChuchuDissappearEscape : public DisappearAndEscapeBase {
    SEAD_RTTI_OVERRIDE(ChuchuDissappearEscape, DisappearAndEscapeBase)
public:
    explicit ChuchuDissappearEscape(const InitArg& arg);
    ~ChuchuDissappearEscape() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
