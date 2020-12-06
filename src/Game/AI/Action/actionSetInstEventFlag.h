#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/Utils/Types.h"

namespace uking::action {

class SetInstEventFlagAction : public ksys::act::ai::Action {
public:
    explicit SetInstEventFlagAction(const InitArg& arg);
    ~SetInstEventFlagAction() override;

    void oneShot() override;
};
KSYS_CHECK_SIZE_NX150(SetInstEventFlagAction, 0x20);

}  // namespace uking::action
