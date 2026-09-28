#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace ksys::act::ai {

class CheckEventCancel : public Query {
    SEAD_RTTI_OVERRIDE(CheckEventCancel, Query)
public:
    explicit CheckEventCancel(const InitArg& arg);
    ~CheckEventCancel() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace ksys::act::ai
