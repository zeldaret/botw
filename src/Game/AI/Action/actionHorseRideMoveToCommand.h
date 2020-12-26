#pragma once

#include "Game/AI/Action/actionHorseRideMoveCommand.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideMoveToCommand : public HorseRideMoveCommand {
    SEAD_RTTI_OVERRIDE(HorseRideMoveToCommand, HorseRideMoveCommand)
public:
    explicit HorseRideMoveToCommand(const InitArg& arg);
    ~HorseRideMoveToCommand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
