#pragma once

#include <thread/seadThread.h>

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

}  // namespace ksys::util
