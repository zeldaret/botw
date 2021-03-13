#pragma once

#include <heap/seadDisposer.h>

namespace ksys::res {

class CompactionMgr;

// Also known as game::ResourceSystem (?)
class GameResourceSystem {
    SEAD_SINGLETON_DISPOSER(GameResourceSystem)
    GameResourceSystem() = default;
    virtual ~GameResourceSystem();

public:
    struct InitArg {
        sead::Heap* heap;
    };

    bool init(const InitArg& arg);

    void calc();
    void pauseCompaction();
    void resumeCompaction();

private:
    CompactionMgr* mCompactionMgr = nullptr;
    bool mPauseCompaction = false;
};

class ScopedCompactionPauser {
public:
    ScopedCompactionPauser() { GameResourceSystem::instance()->pauseCompaction(); }
    ~ScopedCompactionPauser() { GameResourceSystem::instance()->resumeCompaction(); }
    ScopedCompactionPauser(const ScopedCompactionPauser&) = delete;
    ScopedCompactionPauser(ScopedCompactionPauser&&) = delete;
    auto operator=(const ScopedCompactionPauser&) = delete;
    auto operator=(ScopedCompactionPauser&&) = delete;
};

}  // namespace ksys::res
