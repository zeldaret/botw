#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckMapArea : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckMapArea, Query)
public:
    explicit CheckMapArea(const InitArg& arg);
    ~CheckMapArea() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mMapAreaName{};
};

}  // namespace uking::query
