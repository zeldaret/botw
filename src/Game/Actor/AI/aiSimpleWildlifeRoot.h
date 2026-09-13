#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SimpleWildlifeRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SimpleWildlifeRoot, ksys::act::ai::Ai)
public:
    explicit SimpleWildlifeRoot(const InitArg& arg);
    ~SimpleWildlifeRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x30];
    // static_param at offset 0x68
    const int* mInvalidTgtTimerVal_s{};
    // static_param at offset 0x70
    const int* mInvalidEscapeTimerVal_s{};
    // static_param at offset 0x78
    const bool* mIsDeleteWhenDead_s{};
    // static_param at offset 0x80
    const bool* mIsDeadWhenPut_s{};
    // static_param at offset 0x88
    const bool* mIsEscapeWhenPut_s{};
    // static_param at offset 0x90
    const bool* mIsDeadWhenDrop_s{};
    // map_unit_param at offset 0x98
    const bool* mIsPlayerPut_m{};
    // map_unit_param at offset 0xa0
    const bool* mIsLocatorCreate_m{};
    // map_unit_param at offset 0xa8
    const bool* mIsCreateDead_m{};
};

}  // namespace uking::ai
