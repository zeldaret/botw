#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LineCheckTag : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LineCheckTag, ksys::act::ai::Ai)
public:
    explicit LineCheckTag(const InitArg& arg);
    ~LineCheckTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x8];
    // map_unit_param at offset 0x40
    const int* mLineCheckType_m{};
    // map_unit_param at offset 0x48
    const sead::Vector3f* mLineCheckVec_m{};
};

}  // namespace uking::ai
