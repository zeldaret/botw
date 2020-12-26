#pragma once

#include "Game/AI/Action/actionAirWallHorse.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AirWallCurseGanon : public AirWallHorse {
    SEAD_RTTI_OVERRIDE(AirWallCurseGanon, AirWallHorse)
public:
    explicit AirWallCurseGanon(const InitArg& arg);
    ~AirWallCurseGanon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
