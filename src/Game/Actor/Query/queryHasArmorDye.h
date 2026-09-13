#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class HasArmorDye : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(HasArmorDye, Query)
public:
    explicit HasArmorDye(const InitArg& arg);
    ~HasArmorDye() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
