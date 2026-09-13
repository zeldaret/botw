#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OpenItemCategory : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(OpenItemCategory, ksys::act::ai::Action)
public:
    explicit OpenItemCategory(const InitArg& arg);
    ~OpenItemCategory() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mCategory_d{};
};

}  // namespace uking::action
