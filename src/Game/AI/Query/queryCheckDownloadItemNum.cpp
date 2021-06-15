#include "Game/AI/Query/queryCheckDownloadItemNum.h"
#include <evfl/Query.h>

namespace uking::query {

CheckDownloadItemNum::CheckDownloadItemNum(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckDownloadItemNum::~CheckDownloadItemNum() = default;

// FIXME: implement
int CheckDownloadItemNum::doQuery() {
    return -1;
}

void CheckDownloadItemNum::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "CheckNum");
    loadBool(arg.param_accessor, "IsUnityCheckBomb");
}

void CheckDownloadItemNum::loadParams() {
    getDynamicParam(&mCheckNum, "CheckNum");
    getDynamicParam(&mIsUnityCheckBomb, "IsUnityCheckBomb");
}

}  // namespace uking::query
