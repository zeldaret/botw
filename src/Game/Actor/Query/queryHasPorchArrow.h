#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class HasPorchArrow : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(HasPorchArrow, Query)
public:
    explicit HasPorchArrow(const InitArg& arg);
    ~HasPorchArrow() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mCheckNum{};
};

}  // namespace uking::query
