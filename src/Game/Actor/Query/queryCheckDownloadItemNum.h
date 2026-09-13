#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckDownloadItemNum : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckDownloadItemNum, Query)
public:
    explicit CheckDownloadItemNum(const InitArg& arg);
    ~CheckDownloadItemNum() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mCheckNum{};
    bool* mIsUnityCheckBomb{};
};

}  // namespace uking::query
