#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BowEquiped : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BowEquiped, ksys::act::ai::Ai)
public:
    explicit BowEquiped(const InitArg& arg);
    ~BowEquiped() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
};

}  // namespace uking::ai
