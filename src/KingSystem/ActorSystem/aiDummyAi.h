#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::act::ai {

class DummyAi : public Ai {
    SEAD_RTTI_OVERRIDE(DummyAi, Ai)
public:
    explicit DummyAi(const InitArg& arg);

    bool isFlag4Set() const override { return true; }
    void enter_(InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace ksys::act::ai
