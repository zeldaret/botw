#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonBeastWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonBeastWait, ksys::act::ai::Ai)
public:
    explicit GanonBeastWait(const InitArg& arg);
    ~GanonBeastWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    bool* mIsWeakPointAppearMode_a{};
};

}  // namespace uking::ai
