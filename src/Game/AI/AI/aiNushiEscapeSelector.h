#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NushiEscapeSelector : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NushiEscapeSelector, ksys::act::ai::Ai)
public:
    explicit NushiEscapeSelector(const InitArg& arg);
    ~NushiEscapeSelector() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mNumOfAllowedEscapes_s{};
};

}  // namespace uking::ai
