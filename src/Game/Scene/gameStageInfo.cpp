#include "Game/Scene/gameStageInfo.h"
#include "KingSystem/System/StageInfo.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking {

static ksys::util::InitConstants sConstants;
sead::FixedSafeString<256> StageInfo::sStr;
StageInfo StageInfo::sInfo;

const sead::SafeString& StageInfo::getCurrentMapType() {
    return ksys::StageInfo::getCurrentMapType();
}

const sead::SafeString& StageInfo::getCurrentMapName() {
    return ksys::StageInfo::getCurrentMapName();
}

}  // namespace uking
