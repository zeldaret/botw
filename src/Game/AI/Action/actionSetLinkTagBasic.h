#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/Utils/Types.h"

namespace uking::action {

class SetLinkTagBasicAction : public ksys::act::ai::Action {
public:
    SetLinkTagBasicAction(const ksys::act::ai::ClassArg& arg);
    ~SetLinkTagBasicAction() override;

    void enter() override;
    void loadParams() override;

private:
    ksys::act::ai::ParamRef<bool> IsOn;
};
KSYS_CHECK_SIZE_NX150(SetLinkTagBasicAction, 0x28);

}  // namespace uking::action
