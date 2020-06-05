#include "KingSystem/ActorSystem/actBaseProcJob.h"

namespace ksys::act {

BaseProcJobLink::BaseProcJobLink(BaseProc* proc, u8 priority)
    : TListNode(proc), mPriority(priority), mNewPriority(priority), mPriority2(3),
      mNewPriority2(3) {}

}  // namespace ksys::act
