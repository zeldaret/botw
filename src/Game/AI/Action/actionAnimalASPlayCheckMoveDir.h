#pragma once

#include "Game/AI/Action/actionForkAnimalASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalASPlayCheckMoveDir : public ForkAnimalASPlay {
    SEAD_RTTI_OVERRIDE(AnimalASPlayCheckMoveDir, ForkAnimalASPlay)
public:
    explicit AnimalASPlayCheckMoveDir(const InitArg& arg);
    ~AnimalASPlayCheckMoveDir() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
