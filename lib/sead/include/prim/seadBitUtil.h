#pragma once

#include <cstring>

#include <basis/seadTypes.h>

namespace sead
{
// This does not actually seem to exist in Nintendo's sead, but for convenience reasons and to
// easily avoid UB let's pretend this exists.
namespace BitUtil
{
inline void* addOffset(const void* ptr, intptr_t offset)
{
    return reinterpret_cast<void*>(uintptr_t(ptr) + offset);
}

// Convenience function to avoid UB.
// Nintendo appears to perform type punning, but we care about UB.
template <typename To, typename From>
inline To bitCast(From value)
{
    static_assert(sizeof(To) == sizeof(From), "To and From must have the same size");
    To result;
    std::memcpy(&result, &value, sizeof(value));
    return result;
}

// Convenience function to avoid UB.
// Nintendo appears to perform type punning, but we care about UB.
template <typename To>
inline To bitCastPtr(const void* value, intptr_t offset = 0)
{
    To result;
    std::memcpy(&result, addOffset(value, offset), sizeof(To));
    return result;
}

// Convenience function to avoid UB.
// Nintendo appears to perform type punning, but we care about UB.
template <typename To, typename From>
inline void bitCastWrite(const From& value, To* ptr)
{
    static_assert(sizeof(To) == sizeof(From), "To and From must have the same size");
    std::memcpy(ptr, &value, sizeof(To));
}
}  // namespace BitUtil
}  // namespace sead
