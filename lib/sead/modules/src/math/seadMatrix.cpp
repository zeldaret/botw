#include <math/seadMatrix.h>

namespace sead
{
template <>
const Matrix22<f32> Matrix22<f32>::zero(0.0f, 0.0f, 0.0f, 0.0f);

template <>
const Matrix22<f32> Matrix22<f32>::ident(1.0f, 0.0f, 0.0f, 1.0f);

template <>
const Matrix33<f32> Matrix33<f32>::zero(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

template <>
const Matrix33<f32> Matrix33<f32>::ident(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

template <>
const Matrix34<f32> Matrix34<f32>::zero(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                        0.0f, 0.0f);

template <>
const Matrix34<f32> Matrix34<f32>::ident(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                         1.0f, 0.0f);

template <>
const Matrix44<f32> Matrix44<f32>::zero(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);

template <>
const Matrix44<f32> Matrix44<f32>::ident(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                                         1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

template <>
const Matrix22<f64> Matrix22<f64>::zero(0, 0, 0, 0);

template <>
const Matrix22<f64> Matrix22<f64>::ident(1, 0, 0, 1);

template <>
const Matrix33<f64> Matrix33<f64>::zero(0, 0, 0, 0, 0, 0, 0, 0, 0);

template <>
const Matrix33<f64> Matrix33<f64>::ident(1, 0, 0, 0, 1, 0, 0, 0, 1);

template <>
const Matrix34<f64> Matrix34<f64>::zero(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

template <>
const Matrix34<f64> Matrix34<f64>::ident(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0);

template <>
const Matrix44<f64> Matrix44<f64>::zero(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

template <>
const Matrix44<f64> Matrix44<f64>::ident(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

}  // namespace sead
