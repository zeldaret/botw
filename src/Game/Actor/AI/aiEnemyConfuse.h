#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyConfuse : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyConfuse, ksys::act::ai::Ai)
public:
    explicit EnemyConfuse(const InitArg& arg);
    ~EnemyConfuse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mConfuseTime_s{};
};

}  // namespace uking::ai
