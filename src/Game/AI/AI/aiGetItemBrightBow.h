#pragma once

#include "Game/AI/AI/aiGetItemNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GetItemBrightBow : public GetItemNormal {
    SEAD_RTTI_OVERRIDE(GetItemBrightBow, GetItemNormal)
public:
    explicit GetItemBrightBow(const InitArg& arg);
    ~GetItemBrightBow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const float* mGetRadius_s{};
};

}  // namespace uking::ai
