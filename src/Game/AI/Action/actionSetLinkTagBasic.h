#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/Utils/Types.h"

namespace uking::action {

class SetLinkTagBasicAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetLinkTagBasicAction, ksys::act::ai::Action)
public:
    explicit SetLinkTagBasicAction(const InitArg& arg);
    ~SetLinkTagBasicAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

private:
    const bool* IsOn{};
};
KSYS_CHECK_SIZE_NX150(SetLinkTagBasicAction, 0x28);

}  // namespace uking::action
