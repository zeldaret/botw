#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCSaleAppReception : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCSaleAppReception, ksys::act::ai::Action)
public:
    explicit NPCSaleAppReception(const InitArg& arg);
    ~NPCSaleAppReception() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
