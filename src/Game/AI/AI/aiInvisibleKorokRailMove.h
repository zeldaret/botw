#pragma once

#include "Game/AI/AI/aiKorokRailMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InvisibleKorokRailMove : public KorokRailMove {
    SEAD_RTTI_OVERRIDE(InvisibleKorokRailMove, KorokRailMove)
public:
    explicit InvisibleKorokRailMove(const InitArg& arg);
    ~InvisibleKorokRailMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
