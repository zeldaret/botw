#include "Game/AutoPlacement/StringViewCompare.h"
#include <algorithm>

namespace uking {

int compareStringViews(const ore::StringView& lhs, const ore::StringView& rhs) {
    const char* s1 = lhs.data();
    const char* s2 = rhs.data();
    int length = std::min(lhs.size(), rhs.size());
    if (length < 1)
        return lhs.size() - rhs.size();
    while (length-- > 0) {
        if (*s1 == 0 || *s1 != *s2) {
            const int difference = *s1 - *s2;
            if (difference != 0)
                return difference;
            break;
        }
        ++s1;
        ++s2;
    }
    return lhs.size() - rhs.size();
}

}  // namespace uking
