#pragma once

namespace glm {

	namespace detail {

		template<template<length_t C, length_t R, typename T, qualifier Q> class mat, length_t C, length_t R, typename Ret, typename T, qualifier Q>
		struct matrix_functor_1 {
		};

		template<template<length_t C, length_t R, typename T, qualifier Q> class mat, typename Ret, typename T, qualifier Q>
		struct matrix_functor_1<mat, 2, 2, Ret, T, Q> {
			GLM_FUNC_QUALIFIER GLM_CONSTEXPR static mat<2, 2, T, Q> call(Ret (*Func)(T x), mat<2, 2, T, Q> const &x) {
				return mat<2, 2, Ret, Q>(
					Func(x[0][0]), Func(x[0][1]),
					Func(x[1][0]), Func(x[1][1])
				);
			}
		};

		template<template<length_t C, length_t R, typename T, qualifier Q> class mat, typename Ret, typename T, qualifier Q>
		struct matrix_functor_1<mat, 2, 3, Ret, T, Q> {

			GLM_FUNC_QUALIFIER GLM_CONSTEXPR static mat<2, 3, T, Q> call(Ret (*Func)(T x), mat<2, 3, T, Q> const &x) {
				return mat<2, 3, Ret, Q>(
					Func(x[0][0]), Func(x[0][1]), Func(x[0][2]),
					Func(x[1][0]), Func(x[1][1]), Func(x[1][2])
				);
			}

		};

		template<template<length_t C, length_t R, typename T, qualifier Q> class mat, typename Ret, typename T, qualifier Q>
		struct matrix_functor_1<mat, 2, 4, Ret, T, Q> {

			GLM_FUNC_QUALIFIER GLM_CONSTEXPR static mat<2, 4, T, Q> call(Ret (*Func)(T x), mat<2, 4, T, Q> const &x) {
				return mat<2, 4, Ret, Q>(
					Func(x[0][0]), Func(x[0][1]), Func(x[0][2]), Func(x[0][3]),
					Func(x[1][0]), Func(x[1][1]), Func(x[1][2]), Func(x[1][3])
				);
			}

		};

		template<template<length_t C, length_t R, typename T, qualifier Q> class mat, typename Ret, typename T, qualifier Q>
		struct matrix_functor_1<mat, 3, 2, Ret, T, Q> {

			GLM_FUNC_QUALIFIER GLM_CONSTEXPR static mat<3, 2, T, Q> call(Ret (*Func)(T x), mat<3, 2, T, Q> const &x) {
				return mat<3, 2, Ret, Q>(
					Func(x[0][0]), Func(x[0][1]),
					Func(x[1][0]), Func(x[1][1]),
					Func(x[2][0]), Func(x[2][1])
				);
			}

		};

		template<template<length_t C, length_t R, typename T, qualifier Q> class mat, typename Ret, typename T, qualifier Q>
		struct matrix_functor_1<mat, 3, 3, Ret, T, Q> {

			GLM_FUNC_QUALIFIER GLM_CONSTEXPR static mat<3, 3, T, Q> call(Ret (*Func)(T x), mat<3, 3, T, Q> const &x) {
				return mat<3, 3, Ret, Q>(
					Func(x[0][0]), Func(x[0][1]), Func(x[0][2]),
					Func(x[1][0]), Func(x[1][1]), Func(x[1][2]),
					Func(x[2][0]), Func(x[2][1]), Func(x[2][2])
				);
			}

		};

		template<template<length_t C, length_t R, typename T, qualifier Q> class mat, typename Ret, typename T, qualifier Q>
		struct matrix_functor_1<mat, 3, 4, Ret, T, Q> {

			GLM_FUNC_QUALIFIER GLM_CONSTEXPR static mat<3, 4, T, Q> call(Ret (*Func)(T x), mat<3, 4, T, Q> const &x) {
				return mat<3, 4, Ret, Q>(
					Func(x[0][0]), Func(x[0][1]), Func(x[0][2]), Func(x[0][3]),
					Func(x[1][0]), Func(x[1][1]), Func(x[1][2]), Func(x[1][3]),
					Func(x[2][0]), Func(x[2][1]), Func(x[2][2]), Func(x[2][3])
				);
			}

		};

		template<template<length_t C, length_t R, typename T, qualifier Q> class mat, typename Ret, typename T, qualifier Q>
		struct matrix_functor_1<mat, 4, 2, Ret, T, Q> {

			GLM_FUNC_QUALIFIER GLM_CONSTEXPR static mat<4, 2, T, Q> call(Ret (*Func)(T x), mat<4, 2, T, Q> const &x) {
				return mat<4, 2, Ret, Q>(
					Func(x[0][0]), Func(x[0][1]),
					Func(x[1][0]), Func(x[1][1]),
					Func(x[2][0]), Func(x[2][1]),
					Func(x[3][0]), Func(x[3][1])
				);
			}

		};

		template<template<length_t C, length_t R, typename T, qualifier Q> class mat, typename Ret, typename T, qualifier Q>
		struct matrix_functor_1<mat, 4, 3, Ret, T, Q> {

			GLM_FUNC_QUALIFIER GLM_CONSTEXPR static mat<4, 3, T, Q> call(Ret (*Func)(T x), mat<4, 3, T, Q> const &x) {
				return mat<4, 3, Ret, Q>(
					Func(x[0][0]), Func(x[0][1]), Func(x[0][2]),
					Func(x[1][0]), Func(x[1][1]), Func(x[1][2]),
					Func(x[2][0]), Func(x[2][1]), Func(x[2][2]),
					Func(x[3][0]), Func(x[3][1]), Func(x[3][2])
				);
			}

		};

		template<template<length_t C, length_t R, typename T, qualifier Q> class mat, typename Ret, typename T, qualifier Q>
		struct matrix_functor_1<mat, 4, 4, Ret, T, Q> {

			GLM_FUNC_QUALIFIER GLM_CONSTEXPR static mat<4, 4, T, Q> call(Ret (*Func)(T x), mat<4, 4, T, Q> const &x) {
				return mat<4, 4, Ret, Q>(
					Func(x[0][0]), Func(x[0][1]), Func(x[0][2]), Func(x[0][3]),
					Func(x[1][0]), Func(x[1][1]), Func(x[1][2]), Func(x[1][3]),
					Func(x[2][0]), Func(x[2][1]), Func(x[2][2]), Func(x[2][3]),
					Func(x[3][0]), Func(x[3][1]), Func(x[3][2]), Func(x[3][3])
				);
			}

		};

	}

}// namespace glm

/*
 * Copyright (c) 2025 
 * Email: 2523877046@qq.com
 * Author: Baiqiang Long (Buzzlight)
 * 
 * This file is part of the ReduxGL project.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
