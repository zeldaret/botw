#include "KingSystem/ActorSystem/actAiClass.h"

namespace ksys::act::ai {

ActionBase::ActionBase(const ClassArg& arg)
    : mActor{arg.actor}, mDefinitionIdx{u16(arg.definitionIdx)}, mRootIdx{u8(arg.rootIdx)} {}

}  // namespace ksys::act::ai
