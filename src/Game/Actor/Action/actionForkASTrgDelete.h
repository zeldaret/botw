#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgDelete : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASTrgDelete, ksys::act::ai::Action)
public:
    explicit ForkASTrgDelete(const InitArg& arg);
    ~ForkASTrgDelete() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
