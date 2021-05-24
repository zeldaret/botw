#include "Game/AI/Query/queryCheckItemShopPorchVacancy.h"
#include <evfl/Query.h>

namespace uking::query {

CheckItemShopPorchVacancy::CheckItemShopPorchVacancy(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckItemShopPorchVacancy::~CheckItemShopPorchVacancy() = default;

// FIXME: implement
int CheckItemShopPorchVacancy::doQuery() {
    return -1;
}

void CheckItemShopPorchVacancy::loadParams(const evfl::QueryArg& arg) {}

void CheckItemShopPorchVacancy::loadParams() {}

}  // namespace uking::query
