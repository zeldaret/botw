#pragma once

#include "Game/AI/Action/actionInCarryBox.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DragonItemInCarryBox : public InCarryBox {
    SEAD_RTTI_OVERRIDE(DragonItemInCarryBox, InCarryBox)
public:
    explicit DragonItemInCarryBox(const InitArg& arg);
    ~DragonItemInCarryBox() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x30
    bool* mIsInsideObserverArea_a{};
};

}  // namespace uking::action
