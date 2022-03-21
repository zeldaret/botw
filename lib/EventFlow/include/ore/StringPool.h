#pragma once

#include <ore/BinaryFile.h>
#include <ore/Types.h>

namespace ore {

struct StringPool : BinaryBlockHeader {
    int GetLength() const;
    void SetLength(int len);

    BinString* GetFirstString() { return dummy_string.NextString(); }

    u32 reserved_8;
    u32 reserved_c;
    int length;
    BinString dummy_string;
};

}  // namespace ore
