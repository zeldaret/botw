#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormStun : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormStun, ksys::act::ai::Ai)
public:
    explicit SandwormStun(const InitArg& arg);
    ~SandwormStun() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
