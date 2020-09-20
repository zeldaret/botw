#pragma once

#include "KingSystem/Utils/Types.h"

namespace ksys {

// Stubbed in release builds
class StringBoard {
public:
    virtual ~StringBoard() = default;
};
KSYS_CHECK_SIZE_NX150(StringBoard, 0x8);

}  // namespace ksys
