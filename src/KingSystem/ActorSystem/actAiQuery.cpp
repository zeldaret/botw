#include "KingSystem/ActorSystem/actAiQuery.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace ksys::act::ai {

Query::Query(const InitArg& arg) : mActor(arg.actor), mDefIdx(arg.def_idx) {}

template class ClassContainer<Query>;

}  // namespace ksys::act::ai
