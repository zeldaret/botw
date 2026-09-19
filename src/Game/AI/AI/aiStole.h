#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class Stole : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(Stole, ksys::act::ai::Ai)
public:
    bool isChangeable() const override { return true; }
    explicit Stole(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override {}
};

}  // namespace uking::ai
