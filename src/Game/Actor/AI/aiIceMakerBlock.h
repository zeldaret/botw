#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class IceMakerBlock : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(IceMakerBlock, ksys::act::ai::Ai)
public:
    explicit IceMakerBlock(const InitArg& arg);
    ~IceMakerBlock() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x28];
    // static_param at offset 0x60
    const float* mSubRigidStartOffset_s{};
    // static_param at offset 0x68
    const float* mSubRigidEndOffset_s{};
    // static_param at offset 0x70
    const float* mSubRigidExOffset_s{};
};

}  // namespace uking::ai
