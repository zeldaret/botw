#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OpenItemDownloadDemo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(OpenItemDownloadDemo, ksys::act::ai::Action)
public:
    explicit OpenItemDownloadDemo(const InitArg& arg);
    ~OpenItemDownloadDemo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mItemType_d{};
    // dynamic_param at offset 0x28
    bool* mIsEquip_d{};
    // dynamic_param at offset 0x30
    bool* mIsPowerUp_d{};
    // dynamic_param at offset 0x38
    bool* mIsPlayerClose_d{};
};

}  // namespace uking::action
