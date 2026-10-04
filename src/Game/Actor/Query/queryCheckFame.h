#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckFame : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckFame, Query)
public:
    explicit CheckFame(const InitArg& arg);
    ~CheckFame() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mValue{};
};

}  // namespace uking::query
