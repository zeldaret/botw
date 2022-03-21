#include <algorithm>
#include <ore/EnumUtil.h>

namespace ore {

int detail::EnumUtil::FindIndex(int value, const IterRange<const int*>& values) {
    auto it = std::find_if(values.begin(), values.end(), [value](int x) { return value == x; });
    if (it == values.end())
        return -1;
    return static_cast<int>(it - values.begin());
}

}  // namespace ore
