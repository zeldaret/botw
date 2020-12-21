#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class HasEnoughPayment : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(HasEnoughPayment, Query)
public:
    explicit HasEnoughPayment(const InitArg& arg);
    ~HasEnoughPayment() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
