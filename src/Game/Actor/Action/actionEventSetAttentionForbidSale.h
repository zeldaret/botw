#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetAttentionForbidSale : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetAttentionForbidSale, ksys::act::ai::Action)
public:
    explicit EventSetAttentionForbidSale(const InitArg& arg);
    ~EventSetAttentionForbidSale() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
