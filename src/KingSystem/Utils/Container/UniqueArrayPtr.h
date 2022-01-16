#pragma once

#include <basis/seadTypes.h>
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::util {

template <typename T, std::size_t N>
class UniqueArrayPtr {
public:
    UniqueArrayPtr() = default;
    UniqueArrayPtr(const UniqueArrayPtr&) = delete;
    // Not movable either for now.
    UniqueArrayPtr(UniqueArrayPtr&&) = delete;
    ~UniqueArrayPtr() { safeDeleteArray(mData); }

    auto& operator=(const UniqueArrayPtr&) = delete;
    auto& operator=(UniqueArrayPtr&&) = delete;

    T* data() const { return mData; }
    std::size_t size() const { return N; }

    T* begin() const { return mData; }
    T* end() const { return mData + N; }
    T*& operator[](std::size_t i) const { return mData[i]; }

private:
    T* mData = new T[N];
};

}  // namespace ksys::util
