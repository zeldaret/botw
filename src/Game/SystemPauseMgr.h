#pragma once

#include "KingSystem/System/OverlayArenaSystem.h"
#include "KingSystem/Utils/Types.h"

namespace uking {

class SystemPauseMgr : public ksys::ISystemPauseMgr {
public:
    SystemPauseMgr();
    ~SystemPauseMgr() override;

    void m2() override;
    void waitForOnUiActorMgrAndBlockSaveMaybe() override;
    void stopNfpAndWaitForSaveMgr() override;
    void waitForOnUiActorMgr() override;
    void pauseGameSceneAndWait() override;
    bool releaseScreensAndShowMainLayer() override;
    void onSystemPauseResume() override;
    void waitForStageGenFinalStep() override;
    void restoreMainLayerAndResumeGameScene() override;
    bool hideMainLayer() override;
    void openFadeScreen() override;
    void showMainLayerAndResumeProcJobs() override;
    void clearHideMainLayerAndResumeEvents() override;

    bool wasMainLayerVisible() const { return mMainLayerWasVisible; }

private:
    bool mMainLayerWasVisible = true;
};
KSYS_CHECK_SIZE_NX150(SystemPauseMgr, 0x10);

}  // namespace uking
