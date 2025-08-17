#pragma once
#include <GL/glew.h>
#include <iostream>
#include <type_traits>
#include <VertexArray.h>
#include <IndexBuffer.h>
#include <Shader.h>
#include <Texture.h>


/* For General */
#define ASSERT(X) if (!(X)) __debugbreak(); // Accept one predicate expression X and break if it is false
#define GLCall(X) GLClearError();\
    X;\
    ASSERT(GLLogCall(#X,__FILE__,__LINE__));\



/*
* Declare
*/
 
/* For OpenGL */    
template<typename... Args>void BindAll(const Args&...  args);
template<typename... Args>void UnbindAll(const Args&...  args);


void GLClearError();                                              // Clear all OpenGL errors from the error queue
bool GLLogCall(const char* function, const char* file, int line); // Log OpenGL errors, return true if no error, false if there is an error
template <typename T> constexpr bool has_unbind_v = requires(T t) { t.Unbind(); };
template <typename T> constexpr bool has_bind_v = requires (T t) { t.Bind(); };




/*
* Template Implement
*/

template<typename... Args>
void UnbindAll(const Args&...  args)
{
	static int idx = 0;
	auto lambda = [&](const auto& a) {
		if constexpr (has_unbind_v<decltype(a)>)
			a.Unbind();
		else
			std::cout << "Warning! " << idx << " parameter don't have Unbind Member!" << std::endl;
		};
	(lambda(args), ...);

}


template<typename... Args>
void BindAll(const Args&...  args)
{
	int idx = 0;
	auto lambda = [&](const auto& a) {
		idx++;
		if constexpr (has_bind_v<decltype(a)>)
			a.Bind();
		else
			std::cout << "Warning! " << idx << " parameter don't have Bind Member!" << std::endl;

		};
	(lambda(args), ...);

}






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
