#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CarryBox : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CarryBox, ksys::act::ai::Ai)
public:
    explicit CarryBox(const InitArg& arg);
    ~CarryBox() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
