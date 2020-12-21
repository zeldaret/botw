#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckDeadHorseResistered : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckDeadHorseResistered, Query)
public:
    explicit CheckDeadHorseResistered(const InitArg& arg);
    ~CheckDeadHorseResistered() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
