#include "KingSystem/ActorSystem/queryDummyQuery.h"

namespace ksys::act::ai {

DummyQuery::DummyQuery(const Query::InitArg& arg) : Query(arg) {}

bool DummyQuery::init_(sead::Heap* heap) {
    return true;
}

void DummyQuery::loadParams() {}

}  // namespace ksys::act::ai
