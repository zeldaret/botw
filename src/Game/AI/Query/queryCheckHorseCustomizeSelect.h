#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckHorseCustomizeSelect : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckHorseCustomizeSelect, Query)
public:
    explicit CheckHorseCustomizeSelect(const InitArg& arg);
    ~CheckHorseCustomizeSelect() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
