#include "KingSystem/Event/evtActorBindings.h"
#include <evfl/ResActor.h>
#include "KingSystem/Event/evtActorBinding.h"

namespace ksys::evt {

void ActorBindings::allocBindings(sead::Heap* heap) {
    if (mNumActorsToAlloc != 0)
        mBindings.allocBuffer(mNumActorsToAlloc, heap);
}

void ActorBindings::allocBindingsActions(sead::Heap* heap) {
    for (int i = 0; i < mBindings.size(); ++i)
        mBindings[i]->allocActions(heap);
}

void ActorBindings::allocBindingsQueries(sead::Heap* heap) {
    for (int i = 0; i < mBindings.size(); ++i)
        mBindings[i]->allocQueries(heap);
}

ActorBindings::~ActorBindings() {
    for (int i = 0; i < mBindings.size(); ++i) {
        mBindings[i]->finalize();
        delete mBindings[i];
    }
    mBindings.freeBuffer();
}

ActorBinding* ActorBindings::bindActor(const evfl::ResActor* res_actor, sead::Heap* heap) {
    if (mBindings.isBufferReady()) {
        for (int i = 0; i < mBindings.size(); ++i) {
            const char* name = res_actor->name.Get()->data();
            const char* sub_name = res_actor->secondary_name.Get()->data();

            if (sead::SafeString(mBindings[i]->getRes()->name.Get()->data()) != name)
                continue;
            if (sead::SafeString(mBindings[i]->getRes()->secondary_name.Get()->data()) != sub_name)
                continue;
            return mBindings[i];
        }

        auto* binding = new (heap) ActorBinding(res_actor, this);
        mBindings.pushBack(binding);
        return binding;
    }

    ++mNumActorsToAlloc;
    return nullptr;
}

}  // namespace ksys::evt
