#pragma once

#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Thread/Task.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class Handle;
class ResourceUnit;

class TaskRequest : public util::TaskRequest {
    SEAD_RTTI_OVERRIDE(TaskRequest, util::TaskRequest)
public:
    TaskRequest() = default;

    bool mHasResLoadReq = false;
    ResourceUnit* mPackResUnit = nullptr;
    Handle* mResHandle = nullptr;
    sead::FixedSafeString<128> mResPath;
    LoadRequest mResLoadReq;
};
KSYS_CHECK_SIZE_NX150(TaskRequest, 0x180);

}  // namespace ksys::res
