#include "KingSystem/System/Patrol.h"
#include <devenv/seadEnvUtil.h>
#include "KingSystem/Framework/GameConfig.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(Patrol)

Patrol::Patrol() {
    mField0 = GameConfig::getInstance()->_3dd;

    mHasAutoPlay = GameConfig::getInstance()->mPatrolFeatures.include("オートプレイ");
    mHasAutoGenPatroller = GameConfig::getInstance()->mPatrolFeatures.include("AutoGenPatroller");
    mLoadStaticPhysUnstableMapUnit = false;

    mList.initOffset(8);
    sead::EnvUtil::getEnvironmentVariable(&mBuildURL, "BUILD_URL");
}

}  // namespace ksys
