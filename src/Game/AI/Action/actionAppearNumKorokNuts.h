#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AppearNumKorokNuts : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AppearNumKorokNuts, ksys::act::ai::Action)
public:
    explicit AppearNumKorokNuts(const InitArg& arg);
    ~AppearNumKorokNuts() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
