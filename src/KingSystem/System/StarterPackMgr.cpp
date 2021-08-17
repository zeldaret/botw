#include "KingSystem/System/StarterPackMgr.h"

// TODO the LoadRequest stuff should be an inline function

namespace ksys {
namespace res {
// TODO
void setResourceMgrPack(Handle*);
}  // namespace res

SEAD_SINGLETON_DISPOSER_IMPL(StarterPackMgr)

StarterPackMgr::StarterPackMgr() = default;

// TODO
StarterPackMgr::~StarterPackMgr() {
    deleteInstance();
}

// TODO certainly inaccurate
void StarterPackMgr::registerPackFactoryAndMakeOverlayArena(bool reducedHeapSize) {
    if (mExpHeap == nullptr) {
        res::registerEntryFactory(&mArchiveFac, "pack");
        u64 heap_size = 0x1400000;
        if (!reducedHeapSize) {
            heap_size = 0xe100000;
        }
        mExpHeap = sead::ExpHeap::create(
            heap_size, "StarterPackMgr",
            res::ResourceMgrTask::instance()->getArenaForResourceL()->getHeap(), -8,
            sead::Heap::cHeapDirection_Forward, true);
        mOverlayArena = new (mExpHeap, 8) OverlayArena;
        OverlayArena::InitArg arg;
        // TODO
        arg.min_free_percentage = 0.0;
        arg.heap = nullptr;
        arg.heap2 = nullptr;
        arg.name = "StarterPackMgr";
        arg.heap = mExpHeap;
        arg.heap2 = nullptr;
        mOverlayArena->init(arg);
    }
}

void StarterPackMgr::deleteArenaAndHeapAndUnregisterFactory() {
    if (GameConfig::getInstance()->mField419)
        return;
    if (mOverlayArena != nullptr) {
        delete mOverlayArena;
        mOverlayArena = nullptr;
    }
    if (mExpHeap != nullptr) {
        mExpHeap->destroy();
        mExpHeap = nullptr;
    }
    res::unregisterEntryFactory(&mArchiveFac);
}

// TODO
void StarterPackMgr::loadBootupGraphicsPack() {
    if (!GameConfig::getInstance()->mField419) {
        res::registerPackExtension(true, ".pack");
        res::LoadRequest load_req;
        load_req.mRequester = "StarterPackMgr";
        load_req._8 = true;
        load_req._26 = false;
        load_req.mArena = mOverlayArena;
        mTitlePack.requestLoad("Pack/Bootup_Graphics.pack", &load_req, nullptr);
    }
}

// TODO
void StarterPackMgr::loadBootupPacks() {
    if (!GameConfig::getInstance()->mField419) {
        res::registerPackExtension(true, ".pack");
        res::LoadRequest load_req;
        load_req.mRequester = "StarterPackMgr";
        load_req._8 = true;
        load_req._26 = false;
        load_req.mArena = mOverlayArena;
        mBootupPack.requestLoad("Pack/Bootup.pack", &load_req, nullptr);
        sead::FixedSafeString<128> lang_pack;
        sead::RegionLanguageID region_lang = sead::EnvUtil::getRegionLanguage();
        lang_pack.format("Pack/Bootup_%s.pack", region_lang.text());
        mBootupLangPack.requestLoad(lang_pack, &load_req, nullptr);
    }
}

// TODO
void StarterPackMgr::loadTitlePack() {
    if (!GameConfig::getInstance()->mField419) {
        res::registerPackExtension(true, ".pack");
        res::LoadRequest load_req;
        load_req.mRequester = "StarterPackMgr";
        load_req._8 = true;
        load_req._26 = false;
        load_req.mArena = mOverlayArena;
        mTitlePack.requestLoad("Pack/Title.pack", &load_req, nullptr);
    }
}

// TODO
void StarterPackMgr::loadTitleBGPacks() {
    if (!GameConfig::getInstance()->mField419) {
        res::registerPackExtension(true, ".pack");
        res::LoadRequest load_req;
        load_req.mRequester = "StarterPackMgr";
        load_req._8 = true;
        load_req._26 = false;
        load_req.mArena = mOverlayArena;
        mTitleBGPack.requestLoad("Pack/TitleBG.pack", &load_req, nullptr);
        sead::FixedSafeString<128> lang_pack;
        sead::RegionLanguageID region_lang = sead::EnvUtil::getRegionLanguage();
        lang_pack.format("Pack/TitleBG_%s.pack", region_lang.text());
        mBootupLangPack.requestLoad(lang_pack, &load_req, nullptr);
    }
}

void StarterPackMgr::loadAocMainFieldPack() {
    if (uking::aoc::Manager::instance() != nullptr) {
        uking::aoc::Manager::instance()->loadAocMainFieldPack(mOverlayArena);
    }
}

void StarterPackMgr::unloadBootupGraphicsPack() {
    if (GameConfig::getInstance()->mField419)
        return;
    res::setResourceMgrPack(nullptr);
    mBootupGfxPack.requestUnload();
}

bool StarterPackMgr::bootupGraphicsPackReady() {
    if (GameConfig::getInstance()->mField419)
        return true;
    return mBootupGfxPack.isReadyOrNeedsParse();
}

void StarterPackMgr::setPackToBootupGraphics() {
    if (!GameConfig::getInstance()->mField419) {
        mBootupGfxPack.parseResource(nullptr);
        res::registerPackExtension(false, "");
        res::setResourceMgrPack(&mBootupGfxPack);
    }
}

void StarterPackMgr::unloadBootupAndBootupLangPack() {
    if (GameConfig::getInstance()->mField419)
        return;
    res::setResourceMgrPack(nullptr);
    mBootupPack.requestUnload();
    mBootupLangPack.requestUnload();
}

bool StarterPackMgr::bootupPacksReady() {
    if (!GameConfig::getInstance()->mField419) {
        return mBootupPack.isReadyOrNeedsParse() && mBootupLangPack.isReadyOrNeedsParse();
    } else {
        return true;
    }
}

void StarterPackMgr::setPackToBootupPack() {
    if (!GameConfig::getInstance()->mField419) {
        mBootupPack.parseResource(nullptr);
        mBootupLangPack.parseResource(nullptr);
        res::registerPackExtension(false, "");
        res::setResourceMgrPack(&mBootupPack);
    }
}

void StarterPackMgr::unloadTitlePack() {
    if (GameConfig::getInstance()->mField419)
        return;
    res::setResourceMgrPack(nullptr);
    mTitlePack.requestUnload();
}

bool StarterPackMgr::isTitlePackReady() {
    if (GameConfig::getInstance()->mField419)
        return true;
    return mTitlePack.isReadyOrNeedsParse();
}

bool StarterPackMgr::isTitlePackK() {
    if (GameConfig::getInstance()->mField419)
        return true;
    return mTitlePack.hasParsedResource();
}

void StarterPackMgr::setPackToTitlePack() {
    if (!GameConfig::getInstance()->mField419) {
        mTitlePack.parseResource(nullptr);
        res::registerPackExtension(false, "");
        res::setResourceMgrPack(&mTitlePack);
    }
}

void StarterPackMgr::setPackToTitleBGPack() {
    if (!GameConfig::getInstance()->mField419) {
        mTitleBGPack.waitForReady();
        mTitleBGPack.parseResource(nullptr);
        mTitleBGLangPack.waitForReady();
        mTitleBGLangPack.parseResource(nullptr);

        if (uking::aoc::Manager::instance() != nullptr) {
            uking::aoc::Manager::instance()->registerAocMainFieldPack();
        }
        res::registerPackExtension(false, "");
        res::setResourceMgrPack(&mTitleBGPack);
        res::stubbedBool(false);
    }
}

void StarterPackMgr::unloadTitleBGAndAocMainFieldPacksAndStuff() {
    if (GameConfig::getInstance()->mField419)
        return;
    res::setResourceMgrPack(nullptr);
    mTitleBGPack.requestUnload();
    mTitleBGLangPack.requestUnload();

    if (uking::aoc::Manager::instance() != nullptr) {
        uking::aoc::Manager::instance()->unloadAocMainFieldPack();
    }

    for (unsigned char x = 0; x < 5; x++)
        res::ResourceMgrTask::instance()->waitForTaskQueuesToEmpty();

    res::ResourceMgrTask::instance()->resetFlag20000();
}

void StarterPackMgr::failedLoadTitlePack() {
    mTitlePack.requestedLoad();
}

res::Handle* StarterPackMgr::getTitleBGLangPack() {
    res::Handle* ret = &mTitleBGLangPack;
    if (!mTitleBGLangPack.hasParsedResource()) {
        ret = nullptr;
    }
    return ret;
}

res::Handle* StarterPackMgr::getBootupLangPack() {
    if (!mBootupLangPack.hasParsedResource()) {
        return nullptr;
    }
    return &mBootupLangPack;
}

}  // namespace ksys
