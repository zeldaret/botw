#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace ksys::act::ai {

class IsWaitRevival : public Query {
    SEAD_RTTI_OVERRIDE(IsWaitRevival, Query)
public:
    explicit IsWaitRevival(const InitArg& arg);
    ~IsWaitRevival() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace ksys::act::ai
