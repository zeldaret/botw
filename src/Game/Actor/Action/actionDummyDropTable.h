#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actionDummyAction.h"

namespace uking::action {

class DummyDropTable : public ksys::act::ai::DummyAction {
    SEAD_RTTI_OVERRIDE(DummyDropTable, ksys::act::ai::DummyAction)
public:
    explicit DummyDropTable(const InitArg& arg);
    ~DummyDropTable() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    sead::SafeString mDropTable_m{};
};

}  // namespace uking::action
