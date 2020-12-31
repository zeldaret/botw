#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MotorcycleRootBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MotorcycleRootBase, ksys::act::ai::Ai)
public:
    explicit MotorcycleRootBase(const InitArg& arg);
    ~MotorcycleRootBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
