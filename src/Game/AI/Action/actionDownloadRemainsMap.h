#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DownloadRemainsMap : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DownloadRemainsMap, ksys::act::ai::Action)
public:
    explicit DownloadRemainsMap(const InitArg& arg);
    ~DownloadRemainsMap() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mIsPlayerClose_d{};
};

}  // namespace uking::action
