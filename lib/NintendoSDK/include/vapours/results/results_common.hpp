#pragma once
#include <cstdint>
#include <climits>
#include <type_traits>

namespace nn {

    namespace result::detail {

        class ResultTraits {
            public:
                using BaseType = std::uint32_t;
                static const BaseType SuccessValue = BaseType();
                static const int ModuleBits = 9;
                static const int DescriptionBits = 13;
                static const int ReservedBits = 10;
                static_assert(ModuleBits + DescriptionBits + ReservedBits == sizeof(BaseType) * CHAR_BIT, "ModuleBits + DescriptionBits + ReservedBits == sizeof(BaseType) * CHAR_BIT");
            private:
                static BaseType GetBitsValue(BaseType v, int ofs, int num) noexcept {
                    return (v >> ofs) & ~(~BaseType() << num);
                }
            public:
                template<int M, int D>
                struct MakeInnerValueStatic : public std::integral_constant<BaseType, (M) | (D << ModuleBits)> {
                    static_assert(M < (1 << ModuleBits), "Invalid Module");
                    static_assert(D < (1 << DescriptionBits), "Invalid Description");
                };

                static BaseType MakeInnerValue(int m, int d) noexcept {
                    return (static_cast<BaseType>(m) << 0) | (static_cast<BaseType>(d) << ModuleBits);
                }

                static BaseType GetModuleFromValue(BaseType value) noexcept {
                    return GetBitsValue(value, 0, ModuleBits);
                }

                static BaseType GetDescriptionFromValue(BaseType value) noexcept {
                    return GetBitsValue(value, ModuleBits, DescriptionBits);
                }
        };

        /* Use CRTP for Results. */
        template<typename Self>
        class ResultBase {
            public:
                using BaseType = typename ResultTraits::BaseType;
                static const BaseType SuccessValue = ResultTraits::SuccessValue;

                int GetModule() const noexcept {
                    return static_cast<int>(ResultTraits::GetModuleFromValue(static_cast<const Self &>(*this).GetInnerValueForDebug()));
                }

                int GetDescription() const noexcept {
                    return static_cast<int>(ResultTraits::GetDescriptionFromValue(static_cast<const Self &>(*this).GetInnerValueForDebug()));
                }
        };

        class ResultInternalAccessor;

    }

    class ResultSuccess;

    class Result : public result::detail::ResultBase<Result> {
        friend class result::detail::ResultInternalAccessor;
        private:
            using Base = typename result::detail::ResultBase<Result>;
        private:
            BaseType m_value;
        private:
            explicit Result(BaseType v) noexcept : m_value(v) { /* ... */ }
        public:
            Result() noexcept { /* ... */ }

            BaseType GetInnerValueForDebug() const noexcept { return m_value; }

            bool IsSuccess() const noexcept { return m_value == SuccessValue; }
            bool IsFailure() const noexcept { return !IsSuccess(); }

            operator ResultSuccess() const noexcept;
            static bool CanAccept(Result result) noexcept;

            int GetModule() const noexcept { return Base::GetModule(); }
            int GetDescription() const noexcept { return Base::GetDescription(); }
    };
    static_assert(sizeof(Result) == sizeof(result::detail::ResultTraits::BaseType), "sizeof(Result) == sizeof(detail::ResultTraits::BaseType)");
    static_assert(std::is_trivially_destructible<Result>::value, "std::is_trivially_destructible<Result>::value");

    inline bool Result::CanAccept(Result result) noexcept {
        (void)(result);
        return true;
    }

    namespace result::detail {

        class ResultInternalAccessor {
            public:
                static Result ConstructResult(ResultTraits::BaseType v) noexcept { return Result(v); }
        };

        inline Result ConstructResult(ResultTraits::BaseType v) noexcept { return ResultInternalAccessor::ConstructResult(v); }

    }

    class ResultSuccess : public result::detail::ResultBase<ResultSuccess> {
        public:
            using Base = typename result::detail::ResultBase<ResultSuccess>;
        public:
            operator Result() const noexcept { return result::detail::ConstructResult(SuccessValue); }

            BaseType GetInnerValueForDebug() const noexcept { return SuccessValue; }

            bool IsSuccess() const noexcept { return true; }

            static bool CanAccept(Result result) noexcept { return result.IsSuccess(); }

            int GetModule() const noexcept { return Base::GetModule(); }
            int GetDescription() const noexcept { return Base::GetDescription(); }
    };

    namespace result::detail {

        __attribute__((noreturn)) void OnUnhandledResult(Result result) noexcept;

    }

    inline Result::operator ResultSuccess() const noexcept {
        if (!ResultSuccess::CanAccept(*this)) {
            result::detail::OnUnhandledResult(*this);
        }
        return ResultSuccess();
    }

    namespace result::detail {

        template<int Module_, int Description_>
        class ErrorResultBase : public ResultBase<ErrorResultBase<Module_, Description_>> {
            private:
                using Base = ResultBase<ErrorResultBase<Module_, Description_>>;
            public:
                static constexpr int Module = Module_;
                static constexpr int Description = Description_;
                static constexpr typename Base::BaseType InnerValue = ResultTraits::MakeInnerValueStatic<Module, Description>::value;
                static_assert(InnerValue != Base::SuccessValue, "InnerValue != Base::SuccessValue");
            public:
                operator Result() const noexcept { return ConstructResult(InnerValue); }
                operator ResultSuccess() const noexcept { OnUnhandledResult(*this); }

                bool IsSuccess() const noexcept { return false; }

                typename Base::BaseType GetInnerValueForDebug() const noexcept { return InnerValue; }
        };

        template<int Module_, int DescStart, int DescEnd>
        class ErrorRange {
            public:
                static const int Module = Module_;
                static const int DescriptionStart = DescStart;
                static const int DescriptionEnd = DescEnd;
                static_assert(DescriptionStart < DescriptionEnd, "DescriptionStart < DescriptionEnd");
            public:
                static bool Includes(Result result) noexcept {
                    return result.GetModule() == Module && DescriptionStart <= result.GetDescription() && result.GetDescription() < DescriptionEnd;
                }

                friend bool operator <=(Result result, ErrorRange) noexcept {
                    return Includes(result);
                }
        };

    }

}

/* Macros for defining new results. */
#define R_DEFINE_NAMESPACE_RESULT_MODULE(value) namespace detail::result { using ResultModuleId = std::integral_constant<int, value>; }
#define R_CURRENT_NAMESPACE_RESULT_MODULE detail::result::ResultModuleId::value
#define R_NAMESPACE_MODULE_ID(nmspc) nmspc::R_CURRENT_NAMESPACE_RESULT_MODULE

#define R_DEFINE_ERROR_RESULT_IMPL(name, desc_start, desc_end)                                               \
    class Result##name :                                                                                     \
        public ::nn::result::detail::ErrorResultBase<R_CURRENT_NAMESPACE_RESULT_MODULE, desc_start>,         \
        public ::nn::result::detail::ErrorRange<R_CURRENT_NAMESPACE_RESULT_MODULE, desc_start, desc_end + 1> \
        {}

#define R_DEFINE_ABSTRACT_ERROR_RESULT_IMPL(name, desc_start, desc_end) \
    class Result##name :                                                                                     \
        public ::nn::result::detail::ErrorRange<R_CURRENT_NAMESPACE_RESULT_MODULE, desc_start, desc_end + 1> \
        {}


#define R_DEFINE_ERROR_RESULT(name, desc)      R_DEFINE_ERROR_RESULT_IMPL(name, desc, desc)
#define R_DEFINE_ERROR_RANGE(name, start, end) R_DEFINE_ERROR_RESULT_IMPL(name, start, end)

#define R_DEFINE_ABSTRACT_ERROR_RESULT(name, desc)      R_DEFINE_ABSTRACT_ERROR_RESULT_IMPL(name, desc, desc)
#define R_DEFINE_ABSTRACT_ERROR_RANGE(name, start, end) R_DEFINE_ABSTRACT_ERROR_RESULT_IMPL(name, start, end)
