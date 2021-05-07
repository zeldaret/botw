#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::evt {

// FIXME: incomplete
class Metadata {
public:
    Metadata();
    Metadata(const char* event, const char* entry_point, const char* type = "");
    explicit Metadata(const char* event) : Metadata(event, event) {}
    virtual ~Metadata();

private:
    u8 pad_0x8[0x158 - 0x8];
};
KSYS_CHECK_SIZE_NX150(Metadata, 0x158);

}  // namespace ksys::evt
