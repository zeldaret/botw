#pragma once

#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>

namespace ksys::mii {

extern sead::SafeArray<sead::SafeString, 4> s_rot_labels;

// FIXME: incomplete
class ModelCreator final : public sead::hostio::Node {
    SEAD_SINGLETON_DISPOSER(ModelCreator)
public:
    ModelCreator() = default;

    struct Arg {
        int type;
    };

    const sead::SafeString& getActorName(const Arg& arg) const;
};

}  // namespace ksys::mii
