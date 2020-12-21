#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class HasItemDye : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(HasItemDye, Query)
public:
    explicit HasItemDye(const InitArg& arg);
    ~HasItemDye() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
