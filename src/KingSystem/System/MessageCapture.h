#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

class MessageCapture {
    SEAD_SINGLETON_DISPOSER(MessageCapture)
    MessageCapture() = default;
    virtual ~MessageCapture() = default;
};
KSYS_CHECK_SIZE_NX150(MessageCapture, 0x28);

}  // namespace ksys
