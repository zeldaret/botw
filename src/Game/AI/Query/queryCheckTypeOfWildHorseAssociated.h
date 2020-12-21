#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckTypeOfWildHorseAssociated : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckTypeOfWildHorseAssociated, Query)
public:
    explicit CheckTypeOfWildHorseAssociated(const InitArg& arg);
    ~CheckTypeOfWildHorseAssociated() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
