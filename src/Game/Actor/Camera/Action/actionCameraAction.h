#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraAction, ksys::act::ai::Action)
public:
    explicit CameraAction(const InitArg& arg);
    ~CameraAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0x20];
    // static_param at offset 0x40
    const bool* mBowFlag_s{};
};

}  // namespace uking::action
