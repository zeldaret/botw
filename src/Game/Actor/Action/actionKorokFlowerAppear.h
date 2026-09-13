#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class KorokFlowerAppear : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(KorokFlowerAppear, ksys::act::ai::Action)
public:
    explicit KorokFlowerAppear(const InitArg& arg);
    ~KorokFlowerAppear() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
