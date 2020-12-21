#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class IsSoldOut : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(IsSoldOut, Query)
public:
    explicit IsSoldOut(const InitArg& arg);
    ~IsSoldOut() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mTableName{};
};

}  // namespace uking::query
