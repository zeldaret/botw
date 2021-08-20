#include "KingSystem/System/StarterPackMgr.h"

namespace ksys {
SEAD_SINGLETON_DISPOSER_IMPL(StarterPackMgr)

StarterPackMgr::StarterPackMgr() = default;

StarterPackMgr::~StarterPackMgr() = default;

void StarterPackMgr::registerPackFactoryAndMakeOverlayArena(bool reduced_heap_size) {
    if (!mExpHeap) {
        res::registerEntryFactory(&mArchiveFac, "pack");
        sead::Heap* heap = res::ResourceMgrTask::instance()->getArenaForResourceL()->getHeap();
        u64 heap_size;
        if (!reduced_heap_size) {
            heap_size = 0xe100000;
        } else {
            heap_size = 0x1400000;
        }
        mExpHeap = sead::ExpHeap::create(heap_size, "StarterPackMgr", heap, -8,
                                         sead::Heap::cHeapDirection_Forward, true);
        mOverlayArena = new (mExpHeap, 8) OverlayArena;
        OverlayArena::InitArg arg;
        arg.size = mExpHeap->getMaxAllocatableSize(8);
        arg.use_best_fit_alloc_mode = false;
        arg.set_flag_1 = true;
        arg.set_flag_8 = true;
        arg.name = "StarterPackMgr";
        arg.heap = mExpHeap;
        arg.heap2 = nullptr;
        arg._6 = false;
        arg.set_flag_10 = false;
        mOverlayArena->init(arg);
    }
}

void StarterPackMgr::deleteArenaAndHeapAndUnregisterFactory() {
    if (!GameConfig::getInstance()->mField419) {
        if (mOverlayArena) {
            delete mOverlayArena;
            mOverlayArena = nullptr;
        }
        if (mExpHeap) {
            mExpHeap->destroy();
            mExpHeap = nullptr;
        }
        res::unregisterEntryFactory(&mArchiveFac);
    }
}

void StarterPackMgr::loadBootupGraphicsPack() {
    if (!GameConfig::getInstance()->mField419) {
        sead::SafeString extension = ".pack";
        res::registerPackExtension(true, extension);

        res::LoadRequest load_req;
        load_req.mRequester = "StarterPackMgr";
        load_req._8 = true;
        load_req._26 = false;
        load_req.mArena = mOverlayArena;

        mBootupGfxPack.requestLoad("Pack/Bootup_Graphics.pack", &load_req, nullptr);
    }
}

void StarterPackMgr::loadBootupPacks() {
    if (!GameConfig::getInstance()->mField419) {
        sead::SafeString extension = ".pack";
        res::registerPackExtension(true, extension);

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

void StarterPackMgr::loadTitlePack() {
    if (!GameConfig::getInstance()->mField419) {
        sead::SafeString extension = ".pack";
        res::registerPackExtension(true, extension);

        res::LoadRequest load_req;
        load_req.mRequester = "StarterPackMgr";
        load_req._8 = true;
        load_req._26 = false;
        load_req.mArena = mOverlayArena;

        mTitlePack.requestLoad("Pack/Title.pack", &load_req, nullptr);
    }
}

void StarterPackMgr::loadTitleBGPacks() {
    if (!GameConfig::getInstance()->mField419) {
        sead::SafeString extension = ".pack";
        res::registerPackExtension(true, extension);

        res::LoadRequest load_req;
        load_req.mRequester = "StarterPackMgr";
        load_req._8 = true;
        load_req._26 = false;
        load_req.mArena = mOverlayArena;

        mTitleBGPack.requestLoad("Pack/TitleBG.pack", &load_req, nullptr);
        sead::FixedSafeString<128> lang_pack;
        sead::RegionLanguageID region_lang = sead::EnvUtil::getRegionLanguage();
        lang_pack.format("Pack/TitleBG_%s.pack", region_lang.text());
        mTitleBGLangPack.requestLoad(lang_pack, &load_req, nullptr);
    }
}

void StarterPackMgr::loadAocMainFieldPack() {
    if (uking::aoc::Manager::instance())
        uking::aoc::Manager::instance()->loadAocMainFieldPack(mOverlayArena);
}

void StarterPackMgr::unloadBootupGraphicsPack() {
    if (!GameConfig::getInstance()->mField419) {
        res::setResourceMgrPack(nullptr);
        mBootupGfxPack.requestUnload();
    }
}

bool StarterPackMgr::bootupGraphicsPackReady() {
    return GameConfig::getInstance()->mField419 || mBootupGfxPack.isReadyOrNeedsParse();
}

void StarterPackMgr::setPackToBootupGraphics() {
    if (!GameConfig::getInstance()->mField419) {
        mBootupGfxPack.parseResource(nullptr);
        res::registerPackExtension(false, "");
        res::setResourceMgrPack(&mBootupGfxPack);
    }
}

void StarterPackMgr::unloadBootupAndBootupLangPack() {
    if (!GameConfig::getInstance()->mField419) {
        res::setResourceMgrPack(nullptr);
        mBootupPack.requestUnload();
        mBootupLangPack.requestUnload();
    }
}

bool StarterPackMgr::bootupPacksReady() {
    return GameConfig::getInstance()->mField419 ||
           (mBootupPack.isReadyOrNeedsParse() && mBootupLangPack.isReadyOrNeedsParse());
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
    if (!GameConfig::getInstance()->mField419) {
        res::setResourceMgrPack(nullptr);
        mTitlePack.requestUnload();
    }
}

bool StarterPackMgr::isTitlePackReady() {
    return GameConfig::getInstance()->mField419 || mTitlePack.isReadyOrNeedsParse();
}

bool StarterPackMgr::isTitlePackK() {
    return GameConfig::getInstance()->mField419 || mTitlePack.hasParsedResource();
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

        if (uking::aoc::Manager::instance())
            uking::aoc::Manager::instance()->registerAocMainFieldPack();

        res::registerPackExtension(false, "");
        res::setResourceMgrPack(&mTitleBGPack);
        res::stubbedBool(false);
    }
}

void StarterPackMgr::unloadTitleBGAndAocMainFieldPacksAndStuff() {
    if (!GameConfig::getInstance()->mField419) {
        res::setResourceMgrPack(nullptr);
        mTitleBGPack.requestUnload();
        mTitleBGLangPack.requestUnload();

        if (uking::aoc::Manager::instance())
            uking::aoc::Manager::instance()->unloadAocMainFieldPack();

        for (int x = 0; x < 5; x++)
            res::ResourceMgrTask::instance()->waitForTaskQueuesToEmpty();

        res::ResourceMgrTask::instance()->resetFlag20000();
    }
}

void StarterPackMgr::failedLoadTitlePack() {
    mTitlePack.requestedLoad();
}

res::Handle* StarterPackMgr::getTitleBGLangPack() {
    if (!mTitleBGLangPack.hasParsedResource())
        return nullptr;
    return &mTitleBGLangPack;
}

res::Handle* StarterPackMgr::getBootupLangPack() {
    if (!mBootupLangPack.hasParsedResource())
        return nullptr;
    return &mBootupLangPack;
}

}  // namespace ksys
