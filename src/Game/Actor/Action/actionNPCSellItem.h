#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCSellItem : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCSellItem, ksys::act::ai::Action)
public:
    explicit NPCSellItem(const InitArg& arg);
    ~NPCSellItem() override;

protected:
};

}  // namespace uking::action
