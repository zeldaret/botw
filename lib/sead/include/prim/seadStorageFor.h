#pragma once

#include <utility>
#include "basis/seadTypes.h"

namespace sead
{
struct InitializeTag
{
};

struct ZeroInitializeTag
{
};

/// Provides suitably aligned uninitialized storage for a type T.
/// Use this as a std::aligned_storage replacement that is easier to use and less error prone for
/// common cases (std::aligned_storage_t<sizeof(T), alignof(T)>).
template <typename T, bool AutoDestruct = false>
class StorageFor
{
public:
    constexpr StorageFor() = default;

    explicit StorageFor(InitializeTag) { constructDefault(); }

    template <typename... Args>
    explicit StorageFor(InitializeTag, Args&&... args)
    {
        construct(std::forward<Args>(args)...);
    }

    explicit StorageFor(ZeroInitializeTag) : mStorage{} { constructDefault(); }

    template <typename... Args>
    explicit StorageFor(ZeroInitializeTag, Args&&... args) : mStorage{}
    {
        construct(std::forward<Args>(args)...);
    }

    T* constructDefault() { return new (storage()) T; }

    template <typename... Args>
    T* construct(Args&&... args)
    {
        return new (storage()) T(std::forward<Args>(args)...);
    }

    ~StorageFor()
    {
        if constexpr (AutoDestruct)
            destruct();
    }

    /// @warning It is undefined behavior to call this if no object has been constructed.
    void destruct() { data()->~T(); }

    /// @warning It is undefined behavior to call this if no object has been constructed.
    T& ref() { return reinterpret_cast<T&>(mStorage); }

    /// @warning It is undefined behavior to call this if no object has been constructed.
    const T& ref() const { return reinterpret_cast<const T&>(mStorage); }

    /// @warning It is undefined behavior to call this if no object has been constructed.
    T* data() { return reinterpret_cast<T*>(mStorage); }

    /// @warning It is undefined behavior to call this if no object has been constructed.
    const T* data() const { return reinterpret_cast<const T*>(mStorage); }

    /// @warning It is undefined behavior to call this if no object has been constructed.
    T* operator->() { return data(); }
    /// @warning It is undefined behavior to call this if no object has been constructed.
    const T* operator->() const { return data(); }
    /// @warning It is undefined behavior to call this if no object has been constructed.
    T& operator*() { return ref(); }
    /// @warning It is undefined behavior to call this if no object has been constructed.
    const T& operator*() const { return ref(); }

    void* storage() { return mStorage; }
    const void* storage() const { return mStorage; }

private:
    alignas(T) u8 mStorage[sizeof(T)];
};
}  // namespace sead
