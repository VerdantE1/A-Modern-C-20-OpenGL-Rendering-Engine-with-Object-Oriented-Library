/// @ref gtx_fast_square_root
/// @file glm/gtx/fast_square_root.hpp
///
/// @see core (dependence)
///
/// @defgroup gtx_fast_square_root GLM_GTX_fast_square_root
/// @ingroup gtx
///
/// Include <glm/gtx/fast_square_root.hpp> to use the features of this extension.
///
/// Fast but less accurate implementations of square root based functions.
/// - Sqrt optimisation based on Newton's method,
/// www.gamedev.net/community/forums/topic.asp?topic id=139956

#pragma once

// Dependency:
#include "../common.hpp"
#include "../exponential.hpp"
#include "../geometric.hpp"

#ifndef GLM_ENABLE_EXPERIMENTAL
#	error "GLM: GLM_GTX_fast_square_root is an experimental extension and may change in the future. Use #define GLM_ENABLE_EXPERIMENTAL before including it, if you really want to use it."
#elif GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_GTX_fast_square_root extension included")
#endif

namespace glm
{
	/// @addtogroup gtx_fast_square_root
	/// @{

	/// Faster than the common sqrt function but less accurate.
	///
	/// @see gtx_fast_square_root extension.
	template<typename genType>
	GLM_FUNC_DECL genType fastSqrt(genType x);

	/// Faster than the common sqrt function but less accurate.
	///
	/// @see gtx_fast_square_root extension.
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> fastSqrt(vec<L, T, Q> const& x);

	/// Faster than the common inversesqrt function but less accurate.
	///
	/// @see gtx_fast_square_root extension.
	template<typename genType>
	GLM_FUNC_DECL genType fastInverseSqrt(genType x);

	/// Faster than the common inversesqrt function but less accurate.
	///
	/// @see gtx_fast_square_root extension.
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> fastInverseSqrt(vec<L, T, Q> const& x);

	/// Faster than the common length function but less accurate.
	///
	/// @see gtx_fast_square_root extension.
	template<typename genType>
	GLM_FUNC_DECL genType fastLength(genType x);

	/// Faster than the common length function but less accurate.
	///
	/// @see gtx_fast_square_root extension.
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL T fastLength(vec<L, T, Q> const& x);

	/// Faster than the common distance function but less accurate.
	///
	/// @see gtx_fast_square_root extension.
	template<typename genType>
	GLM_FUNC_DECL genType fastDistance(genType x, genType y);

	/// Faster than the common distance function but less accurate.
	///
	/// @see gtx_fast_square_root extension.
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL T fastDistance(vec<L, T, Q> const& x, vec<L, T, Q> const& y);

	/// Faster than the common normalize function but less accurate.
	///
	/// @see gtx_fast_square_root extension.
	template<typename genType>
	GLM_FUNC_DECL genType fastNormalize(genType x);

	/// Faster than the common normalize function but less accurate.
	///
	/// @see gtx_fast_square_root extension.
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL vec<L, T, Q> fastNormalize(vec<L, T, Q> const& x);

	/// @}
}// namespace glm

#include "fast_square_root.inl"

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
