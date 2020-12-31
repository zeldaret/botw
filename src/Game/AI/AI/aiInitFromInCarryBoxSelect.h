#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InitFromInCarryBoxSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(InitFromInCarryBoxSelect, ksys::act::ai::Ai)
public:
    explicit InitFromInCarryBoxSelect(const InitArg& arg);
    ~InitFromInCarryBoxSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsResetInCarryBoxFlag_s{};
    // aitree_variable at offset 0x40
    bool* mIsInitFromCarryBox_a{};
};

}  // namespace uking::ai
