#pragma once

#include "Game/AI/Action/actionChuchuDissappearEscapeBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChuchuDissappearEscape : public ChuchuDissappearEscapeBase {
    SEAD_RTTI_OVERRIDE(ChuchuDissappearEscape, ChuchuDissappearEscapeBase)
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
