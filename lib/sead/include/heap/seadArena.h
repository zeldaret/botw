#ifndef SEAD_ARENA_H_
#define SEAD_ARENA_H_

#include <basis/seadTypes.h>

namespace sead
{
class Arena
{
public:
    Arena();
    ~Arena();

    u8* initialize(size_t size);

    u8* mStart;
    size_t mSize;
    bool mInitWithStartAddress;
};

}  // namespace sead

#endif  // SEAD_ARENA_H_
