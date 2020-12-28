#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCSale : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(NPCSale, ksys::act::ai::Action)
public:
    explicit NPCSale(const InitArg& arg);
    ~NPCSale() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
