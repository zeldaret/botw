#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckRupee : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckRupee, Query)
public:
    explicit CheckRupee(const InitArg& arg);
    ~CheckRupee() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mValue{};
};

}  // namespace uking::query
