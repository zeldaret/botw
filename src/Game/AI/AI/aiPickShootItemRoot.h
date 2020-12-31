#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PickShootItemRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PickShootItemRoot, ksys::act::ai::Ai)
public:
    explicit PickShootItemRoot(const InitArg& arg);
    ~PickShootItemRoot() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mRemainTime_s{};
};

}  // namespace uking::ai
