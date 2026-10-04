#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class HasArmorAlreadyDyed : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(HasArmorAlreadyDyed, Query)
public:
    explicit HasArmorAlreadyDyed(const InitArg& arg);
    ~HasArmorAlreadyDyed() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
