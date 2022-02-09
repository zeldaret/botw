#pragma once

#include <type_traits>

namespace ksys::util {

/// Deletes an object that was allocated with a new expression and sets the pointer to nullptr,
/// preventing it from being accidentally reused.
/// It is safe for the pointer to be already nullptr.
template <typename T>
inline void safeDelete(T*& pointer) {
    delete pointer;
    pointer = nullptr;
}

/// Deletes an array that was allocated with a new[] expression and sets the pointer to nullptr,
/// preventing it from being accidentally reused.
/// It is safe for the pointer to be already nullptr.
template <typename T>
inline void safeDeleteArray(T*& pointer) {
    delete[] pointer;
    pointer = nullptr;
}

template <typename T>
inline void safeDeleteThread(T*& thread, bool is_jam = false) {
    if (!thread)
        return;

    thread->quitAndWaitDoneSingleThread(is_jam);
    safeDelete(thread);
}

template <typename T>
inline void safeDeleteHeap(T*& heap) {
    if (heap) {
        heap->destroy();
        heap = nullptr;
    }
}

/// @warning This does not call T's destructor.
///          This should only be used if T is trivially destructible (or if you know T's destructor
///          can be skipped).
template <typename T>
inline void deallocateObjectUnsafe(T*& pointer) {
    if (pointer) {
        operator delete(pointer);
        pointer = nullptr;
    }
}

/// @warning This does not call T's destructor.
template <typename T>
inline void deallocateObject(T*& pointer) {
    static_assert(std::is_trivially_destructible_v<T>,
                  "T must be trivially destructible: use safeDelete "
                  "(or use deallocateObjectUnsafe if you know T's destructor can be skipped)");
    deallocateObjectUnsafe(pointer);
}

}  // namespace ksys::util
