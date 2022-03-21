#pragma once

#include <optional>
#include <utility>

namespace sead
{
template <typename Function>
class ScopeGuard final
{
public:
    ScopeGuard(Function&& function) : mFunction(std::move(function)) {}
    ScopeGuard(ScopeGuard&& other) noexcept
    {
        mFunction = std::move(other.mFunction);
        other.dismiss();
    }

    ~ScopeGuard() { exit(); }

    void dismiss() { mFunction.reset(); }

    void exit()
    {
        if (!mFunction)
            return;
        (*mFunction)();
        dismiss();
    }

private:
    std::optional<Function> mFunction;
};

/// To work around the lack of CTAD in compilers with incomplete C++17 support.
template <typename Function>
[[nodiscard]] ScopeGuard<Function> makeScopeGuard(Function&& function)
{
    return ScopeGuard<Function>(std::forward<Function>(function));
}
}  // namespace sead
