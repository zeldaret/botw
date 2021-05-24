#include "Game/AI/Query/queryCheckNumOfBuyPicture.h"
#include <evfl/Query.h>

namespace uking::query {

CheckNumOfBuyPicture::CheckNumOfBuyPicture(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckNumOfBuyPicture::~CheckNumOfBuyPicture() = default;

// FIXME: implement
int CheckNumOfBuyPicture::doQuery() {
    return -1;
}

void CheckNumOfBuyPicture::loadParams(const evfl::QueryArg& arg) {}

void CheckNumOfBuyPicture::loadParams() {}

}  // namespace uking::query
