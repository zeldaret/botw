#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RestreintTired : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RestreintTired, ksys::act::ai::Ai)
public:
    explicit RestreintTired(const InitArg& arg);
    ~RestreintTired() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mCentralPos_d{};
    // aitree_variable at offset 0x48
    bool* mIsTryingReturnRestreint_a{};
};

}  // namespace uking::ai
