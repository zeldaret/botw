#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetMaterialVisible : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetMaterialVisible, ksys::act::ai::Action)
public:
    explicit SetMaterialVisible(const InitArg& arg);
    ~SetMaterialVisible() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x20
    const bool* mIsVisible_s{};
    // dynamic_param at offset 0x28
    sead::SafeString mMaterialName_d{};
};

}  // namespace uking::action
