#pragma once

// A delegate is a wrapper around a pointer to member function or a lambda function.
//
// IDelegates: interface types.
// Delegates: implementations of delegates for pointer to member functions (only).
// LambdaDelegates: implementations of delegates for lambda functions (and more generally functors).
// AnyDelegates: type-erased type that can store any Delegate or LambdaDelegate.
//
// Unlike std::function or inplace_function, delegates cannot wrap functions with arbitrary
// signatures. Each category of delegate has several variants:
//
// - XDelegate (no argument, no return value),
// - XDelegateR (no argument),
// - XDelegate1 (1 argument, no return value)
// - XDelegate1R (1 argument)
// - XDelegate2 (2 argument, no return value)
// - XDelegate2R (2 arguments)
//
// To make a lambda delegate, use the makeLambdaDelegate functions, which will return a
// LambdaDelegate with most template arguments automatically deduced.

#include <type_traits>
#include <utility>

#include <basis/seadNew.h>

namespace sead
{
class Heap;

/// Interface of a delegate for a member function with no argument.
class IDelegate
{
public:
    virtual void invoke() = 0;
    virtual IDelegate* clone(Heap*) const { return nullptr; }
    virtual bool isNoDummy() const { return true; }
    void operator()() { return invoke(); }
};

/// @tparam R Return type
template <typename R>
class IDelegateR
{
public:
    virtual R invoke() = 0;
    virtual IDelegateR* clone(Heap*) const { return nullptr; }
    virtual bool isNoDummy() const { return true; }
    R operator()() { return invoke(); }
};

/// Interface of a delegate for a member function with one argument.
/// @tparam A1 Type of the argument
template <typename A1>
class IDelegate1
{
public:
    virtual void invoke(A1 a1) = 0;
    virtual IDelegate1* clone(Heap*) const { return nullptr; }
    virtual bool isNoDummy() const { return true; }
    void operator()(A1 a1) { return invoke(a1); }
};

/// @tparam A1 Type of the argument
/// @tparam R  Return type
template <typename A1, typename R>
class IDelegate1R
{
public:
    virtual R invoke(A1 a1) = 0;
    virtual IDelegate1R* clone(Heap*) const { return nullptr; }
    virtual bool isNoDummy() const { return true; }
    R operator()(A1 a1) { return invoke(a1); }
};

/// Interface of a delegate for a member function with two arguments.
/// @tparam A1 Type of the first argument
/// @tparam A2 Type of the second argument
template <typename A1, typename A2>
class IDelegate2
{
public:
    virtual void invoke(A1 a1, A2 a2) = 0;
    virtual IDelegate2* clone(Heap*) const { return nullptr; }
    virtual bool isNoDummy() const { return true; }
    void operator()(A1 a1, A2 a2) { return invoke(a1, a2); }
};

/// @tparam A1 Type of the first argument
/// @tparam A2 Type of the second argument
/// @tparam R  Return type
template <typename A1, typename A2, typename R>
class IDelegate2R
{
public:
    virtual R invoke(A1 a1, A2 a2) = 0;
    virtual IDelegate2R* clone(Heap*) const { return nullptr; }
    virtual bool isNoDummy() const { return true; }
    R operator()(A1 a1, A2 a2) { return invoke(a1, a2); }
};

/// Base class for delegate implementations.
template <typename T, typename PTMF, typename Base>
class DelegateBase : public Base
{
public:
    DelegateBase() = default;
    DelegateBase(T* instance, PTMF fn) : mInstance(instance), mFunctionPtr(fn) {}

    T* instance() const { return mInstance; }
    void setInstance(T* instance) { mInstance = instance; }
    void setFunction(PTMF fn) { mFunctionPtr = fn; }

    void bind(T* instance, PTMF fn)
    {
        setInstance(instance);
        setFunction(fn);
    }

protected:
    T* mInstance = nullptr;
    PTMF mFunctionPtr = nullptr;
};

/// Partial specialization of DelegateBase for regular function pointers
/// (*not* pointers-to-member-function).
template <typename FunctionPointer, typename Base>
class DelegateBase<void, FunctionPointer, Base> : public Base
{
public:
    DelegateBase() = default;
    explicit DelegateBase(FunctionPointer fn) : mFunctionPtr(fn) {}

    void setFunction(FunctionPointer fn) { mFunctionPtr = fn; }

protected:
    FunctionPointer mFunctionPtr = nullptr;
};

/// Delegate for a member function with no argument.
/// @tparam T  Class type
template <typename T>
class Delegate : public DelegateBase<T, void (T::*)(), IDelegate>
{
public:
    using Base = DelegateBase<T, void (T::*)(), IDelegate>;
    using Base::Base;
    void invoke() override { operator()(); }
    void operator()() const
    {
        if (this->mInstance && this->mFunctionPtr)
            return (this->mInstance->*(this->mFunctionPtr))();
    }
    Delegate* clone(Heap* heap) const override { return new (heap) Delegate(*this); }
};

/// @tparam T  Class type
/// @tparam R  Return type
template <typename T, typename R>
class DelegateR : public DelegateBase<T, R (T::*)(), IDelegateR<R>>
{
public:
    using Base = DelegateBase<T, R (T::*)(), IDelegateR<R>>;
    using Base::Base;
    R invoke() override { return operator()(); }
    R operator()() const
    {
        if (this->mInstance && this->mFunctionPtr)
            return (this->mInstance->*(this->mFunctionPtr))();
        return {};
    }
    DelegateR* clone(Heap* heap) const override { return new (heap) DelegateR(*this); }
};

/// Delegate for a member function with one argument.
/// @tparam T  Class type
/// @tparam A1 Type of the argument
template <typename T, typename A1>
class Delegate1 : public DelegateBase<T, void (T::*)(A1), IDelegate1<A1>>
{
public:
    using Base = DelegateBase<T, void (T::*)(A1), IDelegate1<A1>>;
    using Base::Base;
    void invoke(A1 a1) override { operator()(a1); }
    void operator()(A1 a1) const
    {
        if (this->mInstance && this->mFunctionPtr)
            return (this->mInstance->*(this->mFunctionPtr))(a1);
    }
    Delegate1* clone(Heap* heap) const override { return new (heap) Delegate1(*this); }
};

/// @tparam T  Class type
/// @tparam A1 Type of the argument
/// @tparam R  Return type
template <typename T, typename A1, typename R>
class Delegate1R : public DelegateBase<T, R (T::*)(A1), IDelegate1R<A1, R>>
{
public:
    using Base = DelegateBase<T, R (T::*)(A1), IDelegate1R<A1, R>>;
    using Base::Base;
    R invoke(A1 a1) override { return operator()(a1); }
    R operator()(A1 a1) const
    {
        if (this->mInstance && this->mFunctionPtr)
            return (this->mInstance->*(this->mFunctionPtr))(a1);
        return {};
    }
    Delegate1R* clone(Heap* heap) const override { return new (heap) Delegate1R(*this); }
};

/// Delegate for a member function with two arguments.
/// @tparam T  Class type
/// @tparam A1 Type of the first argument
/// @tparam A2 Type of the second argument
template <typename T, typename A1, typename A2>
class Delegate2 : public DelegateBase<T, void (T::*)(A1, A2), IDelegate2<A1, A2>>
{
public:
    using Base = DelegateBase<T, void (T::*)(A1, A2), IDelegate2<A1, A2>>;
    using Base::Base;
    void invoke(A1 a1, A2 a2) override { return operator()(a1, a2); }
    void operator()(A1 a1, A2 a2) const
    {
        if (this->mInstance && this->mFunctionPtr)
            return (this->mInstance->*(this->mFunctionPtr))(a1, a2);
    }
    Delegate2* clone(Heap* heap) const override { return new (heap) Delegate2(*this); }
};

/// @tparam T  Class type
/// @tparam A1 Type of the first argument
/// @tparam A2 Type of the second argument
/// @tparam R  Return type
template <typename T, typename A1, typename A2, typename R>
class Delegate2R : public DelegateBase<T, R (T::*)(A1, A2), IDelegate2R<A1, A2, R>>
{
public:
    using Base = DelegateBase<T, R (T::*)(A1, A2), IDelegate2R<A1, A2, R>>;
    using Base::Base;
    R invoke(A1 a1, A2 a2) override { return operator()(a1, a2); }
    R operator()(A1 a1, A2 a2) const
    {
        if (this->mInstance && this->mFunctionPtr)
            return (this->mInstance->*(this->mFunctionPtr))(a1, a2);
        return {};
    }
    Delegate2R* clone(Heap* heap) const override { return new (heap) Delegate2R(*this); }
};

class DelegateFunc : public DelegateBase<void, void (*)(), IDelegate>
{
public:
    using Base = DelegateBase<void, void (*)(), IDelegate>;
    using Base::Base;
    void invoke() override { operator()(); }
    void operator()() const
    {
        if (this->mFunctionPtr)
            return (*this->mFunctionPtr)();
    }
    DelegateFunc* clone(Heap* heap) const override { return new (heap) DelegateFunc(*this); }
};

template <typename R>
class DelegateRFunc : public DelegateBase<void, R (*)(), IDelegateR<R>>
{
public:
    using Base = DelegateBase<void, R (*)(), IDelegateR<R>>;
    using Base::Base;
    R invoke() override { return operator()(); }
    R operator()() const
    {
        if (this->mFunctionPtr)
            return (*this->mFunctionPtr)();
        return {};
    }
    DelegateRFunc* clone(Heap* heap) const override { return new (heap) DelegateRFunc(*this); }
};

template <typename A1>
class Delegate1Func : public DelegateBase<void, void (*)(A1), IDelegate1<A1>>
{
public:
    using Base = DelegateBase<void, void (*)(A1), IDelegate1<A1>>;
    using Base::Base;
    void invoke(A1 a1) override { operator()(a1); }
    void operator()(A1 a1) const
    {
        if (this->mFunctionPtr)
            return (*this->mFunctionPtr)(a1);
    }
    Delegate1Func* clone(Heap* heap) const override { return new (heap) Delegate1Func(*this); }
};

template <typename A1, typename R>
class Delegate1RFunc : public DelegateBase<void, R (*)(A1), IDelegate1R<A1, R>>
{
public:
    using Base = DelegateBase<void, R (*)(A1), IDelegate1R<A1, R>>;
    using Base::Base;
    R invoke(A1 a1) override { return operator()(a1); }
    R operator()(A1 a1) const
    {
        if (this->mFunctionPtr)
            return (*this->mFunctionPtr)(a1);
        return {};
    }
    Delegate1RFunc* clone(Heap* heap) const override { return new (heap) Delegate1RFunc(*this); }
};

template <typename A1, typename A2>
class Delegate2Func : public DelegateBase<void, void (*)(A1, A2), IDelegate2<A1, A2>>
{
public:
    using Base = DelegateBase<void, void (*)(A1, A2), IDelegate2<A1, A2>>;
    using Base::Base;
    void invoke(A1 a1, A2 a2) override { return operator()(a1, a2); }
    void operator()(A1 a1, A2 a2) const
    {
        if (this->mFunctionPtr)
            return (*this->mFunctionPtr)(a1, a2);
    }
    Delegate2Func* clone(Heap* heap) const override { return new (heap) Delegate2Func(*this); }
};

template <typename A1, typename A2, typename R>
class Delegate2RFunc : public DelegateBase<void, R (*)(A1, A2), IDelegate2R<A1, A2, R>>
{
public:
    using Base = DelegateBase<void, R (*)(A1, A2), IDelegate2R<A1, A2, R>>;
    using Base::Base;
    R invoke(A1 a1, A2 a2) override { return operator()(a1, a2); }
    R operator()(A1 a1, A2 a2) const
    {
        if (this->mFunctionPtr)
            return (*this->mFunctionPtr)(a1, a2);
        return {};
    }
    Delegate2RFunc* clone(Heap* heap) const override { return new (heap) Delegate2RFunc(*this); }
};

template <typename Lambda>
class LambdaDelegate : public IDelegate
{
public:
    explicit LambdaDelegate(Lambda l) : mLambda(std::move(l)) {}
    auto invoke() override { return mLambda(); }
    auto operator()() const { return mLambda(); }
    auto clone(Heap* heap) const override { return new (heap) LambdaDelegate(*this); }

protected:
    Lambda mLambda;
};

template <typename Lambda, typename R>
class LambdaDelegateR : public IDelegateR<R>
{
public:
    explicit LambdaDelegateR(Lambda l) : mLambda(std::move(l)) {}
    auto invoke() override { return mLambda(); }
    auto operator()() const { return mLambda(); }
    auto clone(Heap* heap) const override { return new (heap) LambdaDelegateR(*this); }

protected:
    Lambda mLambda;
};

template <typename Lambda, typename A1>
class LambdaDelegate1 : public IDelegate1<A1>
{
public:
    explicit LambdaDelegate1(Lambda l) : mLambda(std::move(l)) {}
    auto invoke(A1 a1) override { return mLambda(a1); }
    auto operator()(A1 a1) const { return mLambda(a1); }
    auto clone(Heap* heap) const override { return new (heap) LambdaDelegate1(*this); }

protected:
    Lambda mLambda;
};

template <typename Lambda, typename A1, typename R>
class LambdaDelegate1R : public IDelegate1R<A1, R>
{
public:
    explicit LambdaDelegate1R(Lambda l) : mLambda(std::move(l)) {}
    auto invoke(A1 a1) override { return mLambda(a1); }
    auto operator()(A1 a1) const { return mLambda(a1); }
    auto clone(Heap* heap) const override { return new (heap) LambdaDelegate1R(*this); }

protected:
    Lambda mLambda;
};

template <typename Lambda, typename A1, typename A2>
class LambdaDelegate2 : public IDelegate2<A1, A2>
{
public:
    explicit LambdaDelegate2(Lambda l) : mLambda(std::move(l)) {}
    auto invoke(A1 a1, A2 a2) override { return mLambda(a1, a2); }
    auto operator()(A1 a1, A2 a2) const { return mLambda(a1, a2); }
    auto clone(Heap* heap) const override { return new (heap) LambdaDelegate2(*this); }

protected:
    Lambda mLambda;
};

template <typename Lambda, typename A1, typename A2, typename R>
class LambdaDelegate2R : public IDelegate2R<A1, A2, R>
{
public:
    explicit LambdaDelegate2R(Lambda l) : mLambda(std::move(l)) {}
    auto invoke(A1 a1, A2 a2) override { return mLambda(a1, a2); }
    auto operator()(A1 a1, A2 a2) const { return mLambda(a1, a2); }
    auto clone(Heap* heap) const override { return new (heap) LambdaDelegate2R(*this); }

protected:
    Lambda mLambda;
};

// To work around the lack of CTAD.
template <typename Lambda>
static auto makeLambdaDelegate(Lambda&& l)
{
    return LambdaDelegate<Lambda>(std::forward<Lambda>(l));
}

template <typename Lambda>
static auto makeLambdaDelegateR(Lambda&& l)
{
    using R = std::result_of_t<Lambda()>;
    return LambdaDelegateR<Lambda, R>(std::forward<Lambda>(l));
}

template <typename A1, typename Lambda>
static auto makeLambdaDelegate1(Lambda&& l)
{
    return LambdaDelegate1<Lambda, A1>(std::forward<Lambda>(l));
}

template <typename A1, typename Lambda>
static auto makeLambdaDelegate1R(Lambda&& l)
{
    using R = std::result_of_t<Lambda(A1)>;
    return LambdaDelegate1R<Lambda, A1, R>(std::forward<Lambda>(l));
}

template <typename A1, typename A2, typename Lambda>
static auto makeLambdaDelegate2(Lambda&& l)
{
    return LambdaDelegate2<Lambda, A1, A2>(std::forward<Lambda>(l));
}

template <typename A1, typename A2, typename Lambda>
static auto makeLambdaDelegate2R(Lambda&& l)
{
    using R = std::result_of_t<Lambda(A1, A2)>;
    return LambdaDelegate2R<Lambda, A1, A2, R>(std::forward<Lambda>(l));
}

namespace detail
{
class DummyClassForDelegate
{
};

template <typename Interface, typename AnyClass, size_t StorageSize>
class AnyDelegateImpl
{
public:
    /// Stores a dummy function.
    AnyDelegateImpl() { new (&mStorage) typename AnyClass::UnbindDummy(); }

    /// Stores a function.
    template <typename DelegateType>
    AnyDelegateImpl(DelegateType other)
    {
        *this = std::move(other);
    }

    /// Stores a function.
    template <typename DelegateType>
    AnyDelegateImpl& operator=(DelegateType other)
    {
        static_assert(std::is_trivially_destructible<DelegateType>());
        static_assert(std::is_base_of<Interface, DelegateType>());
        static_assert(sizeof(DelegateType) <= sizeof(mStorage));
        new (&mStorage) DelegateType(std::move(other));
        return *this;
    }

    /// Calls the stored function.
    template <typename... Args>
    auto operator()(Args&&... args)
    {
        return getDelegate()->invoke(std::forward<Args>(args)...);
    }

    /// Calls the stored function.
    template <typename... Args>
    auto operator()(Args&&... args) const
    {
        return getDelegate()->invoke(std::forward<Args>(args)...);
    }

    /// Checks if a non-dummy function is stored.
    explicit operator bool() const { return getDelegate()->isNoDummy(); }

    Interface* getDelegate() { return reinterpret_cast<Interface*>(&mStorage); }
    const Interface* getDelegate() const { return reinterpret_cast<const Interface*>(&mStorage); }

protected:
    using Interface_ = Interface;
    std::aligned_storage_t<StorageSize, alignof(Interface)> mStorage;
};
}  // namespace detail

/// A type-erased delegate that can store either a Delegate or a LambdaDelegate
/// without heap allocations.
class AnyDelegate : public detail::AnyDelegateImpl<IDelegate, AnyDelegate,
                                                   sizeof(Delegate<detail::DummyClassForDelegate>)>
{
public:
    using Base = AnyDelegateImpl;

    class UnbindDummy final : public Base::Interface_
    {
    public:
        void invoke() override {}
        bool isNoDummy() const override { return false; }
    };
    using Base::Base;
    using Base::operator=;
};

template <typename R>
class AnyDelegateR
    : public detail::AnyDelegateImpl<IDelegateR<R>, AnyDelegateR<R>,
                                     sizeof(DelegateR<detail::DummyClassForDelegate, R>)>
{
public:
    using Base = detail::AnyDelegateImpl<IDelegateR<R>, AnyDelegateR<R>,
                                         sizeof(DelegateR<detail::DummyClassForDelegate, R>)>;

    class UnbindDummy final : public Base::Interface_
    {
    public:
        R invoke() override { return {}; }
        bool isNoDummy() const override { return false; }
    };
    using Base::Base;
    using Base::operator=;
};

template <typename A1>
class AnyDelegate1
    : public detail::AnyDelegateImpl<IDelegate1<A1>, AnyDelegate1<A1>,
                                     sizeof(Delegate1<detail::DummyClassForDelegate, A1>)>
{
public:
    using Base = detail::AnyDelegateImpl<IDelegate1<A1>, AnyDelegate1<A1>,
                                         sizeof(Delegate1<detail::DummyClassForDelegate, A1>)>;

    class UnbindDummy final : public Base::Interface_
    {
    public:
        void invoke(A1) override {}
        bool isNoDummy() const override { return false; }
    };
    using Base::Base;
    using Base::operator=;
};

template <typename A1, typename R>
class AnyDelegate1R
    : public detail::AnyDelegateImpl<IDelegate1R<A1, R>, AnyDelegate1R<A1, R>,
                                     sizeof(Delegate1R<detail::DummyClassForDelegate, A1, R>)>
{
public:
    using Base = detail::AnyDelegateImpl<IDelegate1R<A1, R>, AnyDelegate1R<A1, R>,
                                         sizeof(Delegate1R<detail::DummyClassForDelegate, A1, R>)>;

    class UnbindDummy final : public Base::Interface_
    {
    public:
        R invoke(A1) override { return {}; }
        bool isNoDummy() const override { return false; }
    };
    using Base::Base;
    using Base::operator=;
};

template <typename A1, typename A2>
class AnyDelegate2
    : public detail::AnyDelegateImpl<IDelegate2<A1, A2>, AnyDelegate2<A1, A2>,
                                     sizeof(Delegate2<detail::DummyClassForDelegate, A1, A2>)>
{
public:
    using Base = detail::AnyDelegateImpl<IDelegate2<A1, A2>, AnyDelegate2<A1, A2>,
                                         sizeof(Delegate2<detail::DummyClassForDelegate, A1, A2>)>;

    class UnbindDummy final : public Base::Interface_
    {
    public:
        void invoke(A1, A2) override {}
        bool isNoDummy() const override { return false; }
    };
    using Base::Base;
    using Base::operator=;
};

template <typename A1, typename A2, typename R>
class AnyDelegate2R
    : public detail::AnyDelegateImpl<IDelegate2R<A1, A2, R>, AnyDelegate2R<A1, A2, R>,
                                     sizeof(Delegate2R<detail::DummyClassForDelegate, A1, A2, R>)>
{
public:
    using Base =
        detail::AnyDelegateImpl<IDelegate2R<A1, A2, R>, AnyDelegate2R<A1, A2, R>,
                                sizeof(Delegate2R<detail::DummyClassForDelegate, A1, A2, R>)>;

    class UnbindDummy final : public Base::Interface_
    {
    public:
        R invoke(A1, A2) override { return {}; }
        bool isNoDummy() const override { return false; }
    };
    using Base::Base;
    using Base::operator=;
};
}  // namespace sead
