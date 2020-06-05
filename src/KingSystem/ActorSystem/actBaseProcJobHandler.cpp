#include "KingSystem/ActorSystem/actBaseProcJobHandler.h"
#include "KingSystem/ActorSystem/actBaseProc.h"

namespace ksys::act {

BaseProcJobHandler::BaseProcJobHandler(BaseProc* proc) : mLink(proc, proc->getPriority()) {}

}  // namespace ksys::act
