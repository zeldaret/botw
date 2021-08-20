#pragma once

#include <devenv/seadEnvUtil.h>
#include <heap/seadExpHeap.h>
#include <prim/seadSafeString.h>
#include "Game/DLC/aocManager.h"
#include "KingSystem/Framework/GameConfig.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceArchive.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/System/OverlayArena.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {

class StarterPackMgr {
    SEAD_SINGLETON_DISPOSER(StarterPackMgr)
    StarterPackMgr();
    ~StarterPackMgr();

public:
    void registerPackFactoryAndMakeOverlayArena(bool reduced_heap_size);
    void deleteArenaAndHeapAndUnregisterFactory();
    void loadBootupGraphicsPack();
    void loadBootupPacks();
    void loadTitlePack();
    void loadTitleBGPacks();
    void loadAocMainFieldPack();
    void unloadBootupGraphicsPack();
    bool bootupGraphicsPackReady();
    void setPackToBootupGraphics();
    void unloadBootupAndBootupLangPack();
    bool bootupPacksReady();
    void setPackToBootupPack();
    void unloadTitlePack();
    bool isTitlePackReady();
    bool isTitlePackK();
    void setPackToTitlePack();
    void setPackToTitleBGPack();
    void unloadTitleBGAndAocMainFieldPacksAndStuff();
    void failedLoadTitlePack();
    res::Handle* getBootupLangPack();
    res::Handle* getTitleBGLangPack();

private:
    res::Handle mBootupGfxPack;
    res::Handle mBootupPack;
    res::Handle mUnusedPack;
    res::Handle mBootupLangPack;
    res::Handle mTitlePack;
    res::Handle mTitleBGPack;
    res::Handle mTitleBGLangPack;
    OverlayArena* mOverlayArena = nullptr;
    sead::ExpHeap* mExpHeap = nullptr;
    res::EntryFactory<res::Archive> mArchiveFac;
};
KSYS_CHECK_SIZE_NX150(StarterPackMgr, 0x348);

}  // namespace ksys
