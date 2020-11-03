#include "KingSystem/GameData/gdtManager.h"
#include <devenv/seadEnvUtil.h>
#include <framework/seadFramework.h>
#include <thread/seadThreadUtil.h>
#include <time/seadTickTime.h>
#include "KingSystem/GameData/gdtSaveMgr.h"
#include "KingSystem/GameData/gdtTriggerParam.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resResourceGameData.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::gdt {

SEAD_SINGLETON_DISPOSER_IMPL(Manager)

static util::InitTimeInfoEx sInitTimeInfo;

Manager::Manager() {
    mRetryBuffer = nullptr;
    mGimmickResetBuffer = nullptr;
    mFlagBuffer1 = nullptr;
    mFlagBuffer = nullptr;
}

Manager::~Manager() {
    mShopGameDataInfoHandle.requestUnload();

    if (mGameDataHeap) {
        if (mFlagBuffer1) {
            mFlagBuffer1->destroyHeap();
            mFlagBuffer1 = nullptr;
        }

        if (mFlagBuffer) {
            mFlagBuffer->destroyHeap();
            mFlagBuffer = nullptr;
        }

        if (mRetryBuffer) {
            mRetryBuffer->destroyHeap();
            mRetryBuffer = nullptr;
        }

        if (mGimmickResetBuffer) {
            mGimmickResetBuffer->destroyHeap();
            mGimmickResetBuffer = nullptr;
        }

        if (mSaveAreaHeap) {
            mSaveAreaHeap->destroy();
            mSaveAreaHeap = nullptr;
        }

        mGameDataHeap->destroy();
        mGameDataHeap = nullptr;
    }

    if (mGameDataComHeap) {
        mGameDataComHeap->destroy();
        mGameDataComHeap = nullptr;
    }
}

// NON_MATCHING: address differences for the static bgdata_factory that causes different regalloc
void Manager::init(sead::Heap* heap, sead::Framework* framework) {
    sead::TickTime a;
    sead::TickTime b;

    mGameDataHeap = util::DualHeap::create(0xf00000, "GameDataHeap", heap, nullptr, sizeof(void*),
                                           sead::Heap::cHeapDirection_Forward, true);
    mIncrementLogger = new (mGameDataHeap) IncrementLogger;
    SaveMgr::createInstance(mGameDataHeap);

    SaveMgr::InitArg arg;
    arg.heap = mGameDataHeap;
    arg._8 = 0x300000;
    arg.buf_size = 0x100000;
    arg.buf_alignment = 0x200;
    arg.size2 = 0x10000;
    arg.thread_priority = sead::ThreadUtil::ConvertPrioritySeadToPlatform(18);
    arg.thread_affinity = sead::CoreIdMask(sead::CoreId::cSub1);
    arg._1c = 0x7000;
    arg.is_demo = sead::EnvUtil::getRomType() == "Show_2017_1st";
    if (sead::EnvUtil::getRomType() == "RID_Demo") {
        arg.is_demo = true;
        arg.save_rid_demo_dir = "Save/RID_Demo/";
    }

    arg._60 = nullptr;
    if (util::getDebugHeap2())
        arg._68 = 0x80000;

    SaveMgr::instance()->init(arg);

    static res::EntryFactory<res::GameData> bgdata_factory{5.0, 0xc0000};
    res::registerEntryFactory(&bgdata_factory, "bgdata");

    mSaveAreaHeap =
        util::DualHeap::create(0x500000, "SaveAreaHeap", mGameDataHeap, nullptr, sizeof(void*),
                               sead::Heap::cHeapDirection_Reverse, false);

    SaveMgr::instance()->loadGameSaveData();

    KingEditor::instance()->registerComponent(this);

    sead::FixedSafeString<1024> gamedata_sarc_path;
    gamedata_sarc_path.format("%s/%s.%s", "GameData", "gamedata", "sarc");
    loadGameData(gamedata_sarc_path);

    sead::FixedSafeString<1024> shop_gamedata_info_path;
    shop_gamedata_info_path.format("%s/%s.byml", "GameData", "ShopGameDataInfo");
    loadShopGameDataInfo(shop_gamedata_info_path);

    mParam.param1 = &mFlagBuffer1;
    mParam.param = &mFlagBuffer;
    mParamBypassPerm.param1 = &mFlagBuffer1;
    mParamBypassPerm.param = &mFlagBuffer;

    mMethodTreeNode.method_tree_mgr = framework->getMethodTreeMgr();
    mMethodTreeNode.node.setPauseFlag(sead::MethodTreeNode::cPause_None);

    mBitFlags.reset(BitFlag::_1);
    unloadResources();
    mBitFlags.set(BitFlag::_1000);
    mNumFlagsToReset = 0;
}

}  // namespace ksys::gdt
