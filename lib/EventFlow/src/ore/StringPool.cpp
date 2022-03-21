#include <ore/StringPool.h>

namespace ore {

int StringPool::GetLength() const {
    return length;
}

void StringPool::SetLength(int len) {
    length = len;
}

}  // namespace ore
