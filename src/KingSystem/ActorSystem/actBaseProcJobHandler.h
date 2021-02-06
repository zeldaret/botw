#pragma once

#include "KingSystem/ActorSystem/actBaseProcJob.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {

class BaseProcJobHandler {
public:
    explicit BaseProcJobHandler(BaseProc* proc);
    virtual ~BaseProcJobHandler() = default;
    virtual void invoke() = 0;
    virtual void invokeSpecial() {}

    BaseProcJobLink& getLink() { return mLink; }
    const BaseProcJobLink& getLink() const { return mLink; }

protected:
    BaseProcJobLink mLink;
};
KSYS_CHECK_SIZE_NX150(BaseProcJobHandler, 0x30);

}  // namespace ksys::act
