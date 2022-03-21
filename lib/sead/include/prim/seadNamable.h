#ifndef SEAD_NAMABLE_H_
#define SEAD_NAMABLE_H_

#include <prim/seadSafeString.h>

namespace sead
{
class INamable
{
public:
    INamable() = default;
    explicit INamable(const SafeString& name) : mINamableName(name) {}

    const SafeString& getName() const { return mINamableName; }
    void setName(const SafeString& name) { mINamableName = name; }

private:
    SafeString mINamableName = "";
};

}  // namespace sead

#endif  // SEAD_NAMABLE_H_
