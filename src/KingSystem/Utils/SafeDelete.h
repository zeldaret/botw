#pragma once

namespace ksys::util {

template <typename T>
inline void safeDelete(T*& pointer) {
    if (pointer)
        delete pointer;
    pointer = nullptr;
}

template <typename T>
inline void safeDeleteArray(T*& pointer) {
    if (pointer)
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

}  // namespace ksys::util
