#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BeltConveyor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BeltConveyor, ksys::act::ai::Action)
public:
    explicit BeltConveyor(const InitArg& arg);
    ~BeltConveyor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0x28];
    // static_param at offset 0x48
    const float* mASRate_s{};
    // static_param at offset 0x50
    const bool* mIsReverse_s{};
    // static_param at offset 0x58
    sead::SafeString mASName_s{};
    // map_unit_param at offset 0x68
    const float* mRotateSpeed_m{};
};

}  // namespace uking::action
