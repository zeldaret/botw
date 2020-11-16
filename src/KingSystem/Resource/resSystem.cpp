#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Resource/resResourceMgrTask.h"

namespace ksys::res {

bool stubbedLogFunction() {
    return true;
}

bool isHostPath(const sead::SafeString& path) {
    return ResourceMgrTask::instance()->isHostPath(path);
}

bool returnFalse() {
    return false;
}

bool returnFalse2(const sead::SafeString&) {
    return false;
}

bool returnFalse3(const sead::SafeString&) {
    return false;
}

s32 getDefaultAlignment() {
    return 8;
}

}  // namespace ksys::res
