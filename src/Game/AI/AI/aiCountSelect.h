#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CountSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CountSelect, ksys::act::ai::Ai)
public:
    explicit CountSelect(const InitArg& arg);
    ~CountSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mCounter_s{};
};

}  // namespace uking::ai
