#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CanMarkMapPin : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CanMarkMapPin, Query)
public:
    explicit CanMarkMapPin(const InitArg& arg);
    ~CanMarkMapPin() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
