#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ShowPhoto : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ShowPhoto, ksys::act::ai::Action)
public:
    explicit ShowPhoto(const InitArg& arg);
    ~ShowPhoto() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mActorName_d{};
};

}  // namespace uking::action
