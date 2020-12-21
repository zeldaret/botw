#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckOwnedHorseFamiliarity : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckOwnedHorseFamiliarity, Query)
public:
    explicit CheckOwnedHorseFamiliarity(const InitArg& arg);
    ~CheckOwnedHorseFamiliarity() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
