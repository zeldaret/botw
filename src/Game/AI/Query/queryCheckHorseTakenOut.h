#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckHorseTakenOut : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckHorseTakenOut, Query)
public:
    explicit CheckHorseTakenOut(const InitArg& arg);
    ~CheckHorseTakenOut() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
