#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class HasItemDyeSpecifiedColor : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(HasItemDyeSpecifiedColor, Query)
public:
    explicit HasItemDyeSpecifiedColor(const InitArg& arg);
    ~HasItemDyeSpecifiedColor() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
