#pragma once

namespace sead::numbers
{
template <typename T>
inline constexpr T e_v = 2.718281828459045235360287471352662;
template <typename T>
inline constexpr T log2e_v = 1.442695040888963407359924681001892;
template <typename T>
inline constexpr T log10e_v = 0.434294481903251827651128918916605;
template <typename T>
inline constexpr T pi_v = 3.141592653589793238462643383279502;
template <typename T>
inline constexpr T inv_pi_v = 0.318309886183790671537767526745028;
template <typename T>
inline constexpr T inv_sqrtpi_v = 0.564189583547756286948079451560772;
template <typename T>
inline constexpr T ln2_v = 0.693147180559945309417232121458176;
template <typename T>
inline constexpr T ln10_v = 2.302585092994045684017991454684364;
template <typename T>
inline constexpr T sqrt2_v = 1.414213562373095048801688724209698;
template <typename T>
inline constexpr T sqrt3_v = 1.732050807568877293527446341505872;
template <typename T>
inline constexpr T inv_sqrt3_v = 0.577350269189625764509148780501957;
template <typename T>
inline constexpr T egamma_v = 0.577215664901532860606512090082402;
template <typename T>
inline constexpr T phi_v = 1.618033988749894848204586834365638;

inline constexpr double e = e_v<double>;
inline constexpr double log2e = log2e_v<double>;
inline constexpr double log10e = log10e_v<double>;
inline constexpr double pi = pi_v<double>;
inline constexpr double inv_pi = inv_pi_v<double>;
inline constexpr double inv_sqrtpi = inv_sqrtpi_v<double>;
inline constexpr double ln2 = ln2_v<double>;
inline constexpr double ln10 = ln10_v<double>;
inline constexpr double sqrt2 = sqrt2_v<double>;
inline constexpr double sqrt3 = sqrt3_v<double>;
inline constexpr double inv_sqrt3 = inv_sqrt3_v<double>;
inline constexpr double egamma = egamma_v<double>;
inline constexpr double phi = phi_v<double>;

}  // namespace sead::numbers
