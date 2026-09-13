#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FromPopPoolDamageSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FromPopPoolDamageSelect, ksys::act::ai::Ai)
public:
    explicit FromPopPoolDamageSelect(const InitArg& arg);
    ~FromPopPoolDamageSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
