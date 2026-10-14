#pragma once

#include <ore/StringView.h>

namespace uking {

// Inferred const-reference interface to the original placement-name comparator.
// The descriptive name does not claim an original source symbol.
int compareStringViews(const ore::StringView& lhs, const ore::StringView& rhs);

}  // namespace uking
