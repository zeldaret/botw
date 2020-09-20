#pragma once

namespace ksys {
class OverlayArena;
}

namespace ksys::res {

// FIXME: very, very incomplete.
class ResourceMgrTask {
public:
    static ResourceMgrTask* instance() { return sInstance; }

    void insertOverlayArena(OverlayArena* arena);
    OverlayArena* getSomeArena() const;

private:
    static ResourceMgrTask* sInstance;
};

}  // namespace ksys::res
