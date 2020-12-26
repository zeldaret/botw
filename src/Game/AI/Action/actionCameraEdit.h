#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEdit : public ActionEx {
    SEAD_RTTI_OVERRIDE(CameraEdit, ActionEx)
public:
    explicit CameraEdit(const InitArg& arg);
    ~CameraEdit() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const char* mNormal_s{};
    // static_param at offset 0x28
    const char* mLockOn_s{};
    // static_param at offset 0x30
    const char* mWall_s{};
    // static_param at offset 0x38
    const char* mNormalSubject_s{};
    // static_param at offset 0x40
    const char* mBow_s{};
    // static_param at offset 0x48
    const char* mBowSquat_s{};
    // static_param at offset 0x50
    const char* mBowLockOn_s{};
};

}  // namespace uking::action
