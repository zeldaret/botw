#pragma once

#include <framework/seadCalculateTask.h>
#include <hostio/seadHostIONode.h>
#include "KingSystem/Resource/resUnit.h"

namespace sead {
class Heap;
}

namespace ksys {
class OverlayArena;

namespace util {
class TaskThread;
}
}  // namespace ksys

namespace ksys::res {

// FIXME: very, very incomplete.
class ResourceMgrTask : public sead::CalculateTask, public sead::hostio::Node {
public:
    static ResourceMgrTask* instance() { return sInstance; }

    void insertOverlayArena(OverlayArena* arena);
    OverlayArena* getSomeArena() const;

    util::TaskThread* makeResourceLoadingThread(sead::Heap* heap, bool use_game_task_thread);

    struct GetUnitArg {
        const ResourceUnit::InitArg* unit_init_arg;
        OverlayArena* arena;
    };
    ResourceUnit* clearCachesAndGetUnit(const GetUnitArg& arg);

    void eraseUnit(ResourceUnit* unit);

    struct ClearCacheArg {
        ResourceUnit* unit;
    };
    void clearCache(ClearCacheArg& arg, void* x = nullptr);

    bool dropSFromExtensionIfNeeded(const sead::SafeString& path,
                                    sead::BufferedSafeString& new_path, s32 dot_idx,
                                    const sead::SafeString& extension);

private:
    static ResourceMgrTask* sInstance;
};
KSYS_CHECK_SIZE_NX150(sead::TaskBase, 0xd0);
KSYS_CHECK_SIZE_NX150(sead::MethodTreeNode, 0x98);

}  // namespace ksys::res
