#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ItemConductor : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ItemConductor, ksys::act::ai::Ai)
public:
    explicit ItemConductor(const InitArg& arg);
    ~ItemConductor() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
