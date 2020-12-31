#pragma once

#include "Game/AI/AI/aiAddCarriedBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AddCarried : public AddCarriedBase {
    SEAD_RTTI_OVERRIDE(AddCarried, AddCarriedBase)
public:
    explicit AddCarried(const InitArg& arg);
    ~AddCarried() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
