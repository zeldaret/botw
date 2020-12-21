#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace ksys::act::ai {

class DummyBehavior : public Behavior {
    SEAD_RTTI_OVERRIDE(DummyBehavior, Behavior)
public:
    explicit DummyBehavior(const InitArg& arg);
};

}  // namespace ksys::act::ai
