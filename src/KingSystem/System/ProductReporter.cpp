#include "KingSystem/System/ProductReporter.h"

#include <gfx/seadCamera.h>
#include <heap/seadExpHeap.h>
#include <heap/seadHeap.h>
#include <nn/account.h>
#include <nn/oe.h>

#include "KingSystem/Framework/Framework.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/System/CameraMgr.h"
#include "KingSystem/System/PlayReportMgr.h"
#include "KingSystem/System/VFR.h"

namespace ksys {

static WorkTimes sWorkTimes;

auto& getWorkTimes() {
    return sWorkTimes;
};

[[gnu::noinline]] void ProductReporter::terminate() {
    if (mIsInitalized) {
        gdt::Manager::instance()->removeReinitCallback(mSlot);
        mIsInitalized = false;
    }
}

ProductReporter::~ProductReporter() {
    terminate();
}

void ProductReporter::init(sead::Heap* heap) {
    if (mIsInitalized)
        return;

    mHeap = sead::ExpHeap::create(0x18000, "ProductReporter Heap", heap, sizeof(void*),
                                  sead::Heap::cHeapDirection_Forward, true);

    nn::account::Initialize();

    s32 listAllUsersRet = -1;
    nn::account::Uid uid[8];
    nn::account::ListAllUsers(&listAllUsersRet, uid, 8);

    if (0 < listAllUsersRet) {
        for (int i = 0; i < PlayReportKey::size(); i++)
            mGameDataHandles[i] = gdt::InvalidHandle;

        mPlayerTrackReporter = new (heap) PlayerTrackReporter;
        mPlayerTrackReporter->init(heap);

        mContainer1.init(heap, 0x20, 0x30);
        mContainer2.init(heap, 0x20, 0x30);
        mContainer3.init(heap, 0x20, 0x30);
        mContainer4.init(heap, 0x20, 0x30);

        mIsInitalized = true;
    }
}

void ProductReporter::initGameDataIterators() {
    for (int i = 0; i < PlayReportKey::size(); i++) {
        mGameDataHandles[i] = gdt::Manager::instance()->getS32Handle(PlayReportKey::text(i));
    }
}

bool ProductReporter::isEnabled() const {
    return mEnabled;
}

s32 ProductReporter::getRomWorkTime() const {
    return sWorkTimes.rom;
}

s32 ProductReporter::getSceneWorkTime() const {
    return sWorkTimes.scene;
}

void ProductReporter::resetSceneWorkTime() {
    sWorkTimes.scene = 0;
}

void ProductReporter::updateTimers() {
    if (!mEnabled)
        return;

    mIncrementWorkTimesTimer += VFR::instance()->getIntervalRatio();

    if (mIncrementWorkTimesTimer >= 30.0f) {
        mIncrementWorkTimesTimer -= 30.0f;
        if (incrementSceneAndRomWorkTime()) {
            mPlayerTrackReporter->setPosTrackEnd();
        }
    }

    mNinetyTickTimer += VFR::instance()->getIntervalRatio();
    if (!(90.0f > mNinetyTickTimer)) {
        mNinetyTickTimer -= 90.0f;
    }
}

bool ProductReporter::saveReport(PlayReport* playReport) const {
    if (playReport != nullptr && mEnabled) {
        return playReport->save();
    }

    return false;
}

bool ProductReporter::incrementSceneAndRomWorkTime() {
    const auto get_flag = [this](auto key, s32* value) {
        gdt::Manager::instance()->getS32(mGameDataHandles[key], value);
    };

    const auto set_flag = [this](auto key, s32 value) {
        gdt::Manager::instance()->setS32(value, mGameDataHandles[key]);
    };

    const auto increment = [this, &get_flag, &set_flag](auto key, s32* value) {
        get_flag(key, value);
        set_flag(key, *value + 1);
    };

    if (map::PlacementMgr::instance() == nullptr)
        return false;

    s32 value = 0;
    sWorkTimes.rom++;
    sWorkTimes.scene++;

    auto* camera = CameraMgr::instance()->getLookAtCamera();

    if (camera != nullptr && mPos != camera->getPos()) {
        mCameraIdleTimer = 0.0f;
        mPos = camera->getPos();
    }

    if (!(mCameraIdleTimer < 300.0f))
        return false;

    mCameraIdleTimer += 1.0f;

    increment(PlayReportKey::PlayReport_AllPlayTime, &value);
    increment(PlayReportKey::PlayReport_PlayTime, &value);

    {
        s32 value = 0;
        auto* framework = frm::Framework::instance();

        switch (framework->mOperationMode) {
        case nn::oe::OperationMode_Handheld:
            increment(PlayReportKey::PlayReport_PlayTime_Handheld, &value);

            switch (mCtrlMode) {
            case 1:
                increment(PlayReportKey::PlayReport_CtrlMode_Free, &value);
                break;
            case 2:
                increment(PlayReportKey::PlayReport_CtrlMode_Ext, &value);
                break;
            case 3:
                increment(PlayReportKey::PlayReport_CtrlMode_FullKey, &value);
                break;
            case 4:
                increment(PlayReportKey::PlayReport_CtrlMode_Handheld, &value);
                break;
            default:
                break;
            }

            break;

        case nn::oe::OperationMode_Docked:
            increment(PlayReportKey::PlayReport_PlayTime_Console, &value);

            switch (mCtrlMode) {
            case 1:
                increment(PlayReportKey::PlayReport_CtrlMode_Console_Free, &value);
                break;
            case 2:
                increment(PlayReportKey::PlayReport_CtrlMode_Console_Ext, &value);
                break;
            case 3:
                increment(PlayReportKey::PlayReport_CtrlMode_Console_FullKey, &value);
                break;
            default:
                break;
            }

            break;
        }
    }

    {
        s32 value = 0;

        auto* snd = snd::SoundMgr::instance();
        if (snd == nullptr)
            return true;

        switch (snd->mAudioChannelType) {
        case snd::AudioChannelType::Mono:
            increment(PlayReportKey::PlayReport_AudioChannel_Mono, &value);
            break;
        case snd::AudioChannelType::Stereo:
            increment(PlayReportKey::PlayReport_AudioChannel_Stereo, &value);
            break;
        case snd::AudioChannelType::_5_1ch:
            increment(PlayReportKey::PlayReport_AudioChannel_5_1ch, &value);
            break;
        default:
            increment(PlayReportKey::PlayReport_AudioChannel_Other, &value);
            break;
        }
    }

    return true;
}

#define PRODUCT_REPORTER_S32_GETTER(NAME, PLAY_REPORT_KEY)                                         \
    s32 ProductReporter::NAME() const {                                                            \
        s32 out = 0;                                                                               \
        gdt::Manager::instance()->getS32(mGameDataHandles[PLAY_REPORT_KEY], &out);                 \
        return out;                                                                                \
    }

PRODUCT_REPORTER_S32_GETTER(getPlayTime, PlayReportKey::PlayReport_PlayTime)
PRODUCT_REPORTER_S32_GETTER(getAllPlayTime, PlayReportKey::PlayReport_AllPlayTime)
PRODUCT_REPORTER_S32_GETTER(getCtrlModeFree, PlayReportKey::PlayReport_CtrlMode_Free)
PRODUCT_REPORTER_S32_GETTER(getCtrlModeExt, PlayReportKey::PlayReport_CtrlMode_Ext)
PRODUCT_REPORTER_S32_GETTER(getCtrlModeFullKey, PlayReportKey::PlayReport_CtrlMode_FullKey)
PRODUCT_REPORTER_S32_GETTER(getCtrlModeHandheld, PlayReportKey::PlayReport_CtrlMode_Handheld)
PRODUCT_REPORTER_S32_GETTER(getCtrlModeConsoleFree, PlayReportKey::PlayReport_CtrlMode_Console_Free)
PRODUCT_REPORTER_S32_GETTER(getCtrlModeConsoleExt, PlayReportKey::PlayReport_CtrlMode_Console_Ext)
PRODUCT_REPORTER_S32_GETTER(getCtrlModeConsoleFullKey,
                            PlayReportKey::PlayReport_CtrlMode_Console_FullKey)
PRODUCT_REPORTER_S32_GETTER(getCtrlModePlayTimeHandheld,
                            PlayReportKey::PlayReport_PlayTime_Handheld)
PRODUCT_REPORTER_S32_GETTER(getPlayTimeConsole, PlayReportKey::PlayReport_PlayTime_Console)

#undef PRODUCT_REPORTER_S32_GETTER

}  // namespace ksys