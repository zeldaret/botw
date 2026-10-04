#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CameraEventConnectTypeSpecify : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CameraEventConnectTypeSpecify, ksys::act::ai::Action)
public:
    explicit CameraEventConnectTypeSpecify(const InitArg& arg);

protected:
};

}  // namespace uking::action
