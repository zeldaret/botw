#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class InCarryBox : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(InCarryBox, ksys::act::ai::Action)
public:
    explicit InCarryBox(const InitArg& arg);
    ~InCarryBox() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    bool* mIsInitFromCarryBox_a{};
};

}  // namespace uking::action
