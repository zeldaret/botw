#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AppearFullPouchInfo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AppearFullPouchInfo, ksys::act::ai::Action)
public:
    explicit AppearFullPouchInfo(const InitArg& arg);
    ~AppearFullPouchInfo() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mPorchItemName_d{};
};

}  // namespace uking::action
