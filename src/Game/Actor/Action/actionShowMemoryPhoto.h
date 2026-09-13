#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ShowMemoryPhoto : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ShowMemoryPhoto, ksys::act::ai::Action)
public:
    explicit ShowMemoryPhoto(const InitArg& arg);
    ~ShowMemoryPhoto() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mPhotoNo_d{};
};

}  // namespace uking::action
