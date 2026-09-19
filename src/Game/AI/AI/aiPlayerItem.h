#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerItem : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerItem, ksys::act::ai::Ai)
public:
    bool isChangeable() const override { return false; }
    explicit PlayerItem(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
