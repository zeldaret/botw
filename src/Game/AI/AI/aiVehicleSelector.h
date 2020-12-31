#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class VehicleSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(VehicleSelector, ksys::act::ai::Ai)
public:
    explicit VehicleSelector(const InitArg& arg);
    ~VehicleSelector() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::ai
