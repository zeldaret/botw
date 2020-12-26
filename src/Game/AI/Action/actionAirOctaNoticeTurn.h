#pragma once

#include "Game/AI/Action/actionNoticeTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AirOctaNoticeTurn : public NoticeTurn {
    SEAD_RTTI_OVERRIDE(AirOctaNoticeTurn, NoticeTurn)
public:
    explicit AirOctaNoticeTurn(const InitArg& arg);
    ~AirOctaNoticeTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
