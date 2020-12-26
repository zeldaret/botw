#pragma once

#include "Game/AI/Action/actionForkASTrgAerialTurn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgForceDirAerialTurn : public ForkASTrgAerialTurn {
    SEAD_RTTI_OVERRIDE(ForkASTrgForceDirAerialTurn, ForkASTrgAerialTurn)
public:
    explicit ForkASTrgForceDirAerialTurn(const InitArg& arg);
    ~ForkASTrgForceDirAerialTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const int* mDir_s{};
};

}  // namespace uking::action
