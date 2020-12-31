#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CameraEditRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CameraEditRoot, ksys::act::ai::Ai)
public:
    explicit CameraEditRoot(const InitArg& arg);

    bool init_(sead::Heap* heap) override;

protected:
};

}  // namespace uking::ai
