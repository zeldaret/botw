#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AreaBase, ksys::act::ai::Action)
public:
    explicit AreaBase(const InitArg& arg);

    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const bool* mEnableCharacterOn_m{};
};

}  // namespace uking::action
