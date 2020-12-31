#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalEnemyDoShootPartSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StalEnemyDoShootPartSelect, ksys::act::ai::Ai)
public:
    explicit StalEnemyDoShootPartSelect(const InitArg& arg);
    ~StalEnemyDoShootPartSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mShootRate_s{};
};

}  // namespace uking::ai
