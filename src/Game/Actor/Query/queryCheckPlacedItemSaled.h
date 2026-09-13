#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckPlacedItemSaled : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckPlacedItemSaled, Query)
public:
    explicit CheckPlacedItemSaled(const InitArg& arg);
    ~CheckPlacedItemSaled() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
