#pragma once

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
class ResourceMgrTask {
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

}  // namespace ksys::res
