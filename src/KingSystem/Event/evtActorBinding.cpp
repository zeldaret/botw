#include "KingSystem/Event/evtActorBinding.h"
#include <evfl/ResActor.h>
#include <ore/ResMetaData.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Event/evtActorBindings.h"

namespace ksys::evt {

void ActorBinding::bindAction(const evfl::ResAction* action) {
    if (mActions.isBufferReady())
        mActions.pushBack(action);
    else
        ++mNumActionsToAlloc;
}

void ActorBinding::bindQuery(const evfl::ResQuery* query) {
    if (mQueries.isBufferReady())
        mQueries.pushBack(query);
    else
        ++mNumQueriesToAlloc;
}

sead::SafeString ActorBinding::getActorName() const {
    return mResActor->name.Get()->data();
}

sead::SafeString ActorBinding::getActorSubName() const {
    return mResActor->secondary_name.Get()->data();
}

static bool isSelfOrStarter(const sead::SafeString& name) {
    return name.findIndex("Self") == 0 || name.findIndex("Starter") == 0;
}

ActorBinding::ActorCreateMode ActorBinding::getActorCreateMode(const act::Actor* actor) const {
    if (getActorName() == "GameROMPlayer")
        return ActorCreateMode::k4;

    if (getActorName() == "GameRomCamera")
        return ActorCreateMode::k5;

    if (getActorName() == "Current")
        return ActorCreateMode::k8;

    if (getActorName() == "Argument")
        return ActorCreateMode::k8;

    if (isSelfOrStarter(getActorName()))
        return ActorCreateMode::k7;

    if (getActorName() == "SignalFlowchart")
        return ActorCreateMode::k7;

    const sead::SafeString actor_name = getActorName();
    if (actor_name == "DemoXLinkActor")
        return ActorCreateMode::k6;

    if (mResActor->HasArgumentName())
        return ActorCreateMode::k7;

    const auto* params = mResActor->params.Get();
    if (!params)
        return ActorCreateMode::k7;

    auto* create_mode = params->Get("CreateMode", ore::ResMetaData::DataType::kInt);
    if (!create_mode)
        return ActorCreateMode::k0;

    switch (create_mode->value.i) {
    case 0: {
        if (!mParent->isInitialized())
            return ActorCreateMode::k0;

        const char* profile_c;
        act::InfoData::instance()->getActorProfile(&profile_c, actor_name.cstr());
        const sead::SafeString profile = profile_c;

        if (actor && actor->getName() == getActorName() && getActorSubName().isEmpty())
            return ActorCreateMode::k7;

        if (profile == "EventSystem" || profile == "ComplexTag" || profile == "SoleTag" ||
            profile == "System" || profile == "EventTag") {
            return ActorCreateMode::k0;
        }

        return ActorCreateMode::k1;
    }
    case 1:
        return ActorCreateMode::k0;
    case 2:
    default:
        return ActorCreateMode::k1;
    case 3:
        return ActorCreateMode::k2;
    case 4:
        return ActorCreateMode::k3;
    }
}

}  // namespace ksys::evt
