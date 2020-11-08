#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include "KingSystem/ActorSystem/actASSetting.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(ActorParamMgr)

ActorParamMgr::ActorParamMgr() = default;

ActorParamMgr::~ActorParamMgr() {
    ASSetting::deleteInstance();
}

}  // namespace ksys::act
