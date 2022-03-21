#pragma once

#include "heap/seadDisposer.h"
#include "hostio/seadHostIONode.h"
#include "prim/seadSafeString.h"

namespace sead
{
class GameConfig : public hostio::Node
{
    SEAD_SINGLETON_DISPOSER(GameConfig)
    GameConfig();
    virtual ~GameConfig();

    static const SafeString cNodeName;

protected:
    struct FileWriteCallback
    {
        virtual ~FileWriteCallback();
        virtual void save();
    };
};
}  // namespace sead
