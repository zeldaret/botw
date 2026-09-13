#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCSellApp : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCSellApp, ksys::act::ai::Action)
public:
    explicit NPCSellApp(const InitArg& arg);
    ~NPCSellApp() override;

protected:
};

}  // namespace uking::action
