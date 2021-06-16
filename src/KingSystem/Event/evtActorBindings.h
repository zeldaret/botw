#pragma once

#include <container/seadPtrArray.h>

namespace ksys::evt {

class ActorBinding;

// TODO
class ActorBindings {
public:
    ActorBindings();
    virtual ~ActorBindings();

    int getNumActors() const { return mNumActors; }
    int isInitialized() const { return mInitialized; }

private:
    sead::PtrArray<ActorBinding> mBindings;
    int mNumActors = 0;
    int mInitialized = 0;
};

}  // namespace ksys::evt
