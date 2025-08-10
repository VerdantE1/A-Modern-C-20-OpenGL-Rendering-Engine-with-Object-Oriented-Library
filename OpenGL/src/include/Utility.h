#pragma once
#include <GL/glew.h>
#include <iostream>
#include <type_traits>
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
			std::cout << "Warning! " << idx << "parameter don't have Unbind Member!" << std::endl;
		};
	(lambda(args), ...);

}


template<typename... Args>
void BindAll(const Args&...  args)
{
	static int idx = 0;
	auto lambda = [&](const auto& a) {
		if constexpr (has_unbind_v<decltype(a)>)
			a.Bind();
		else
			std::cout << "Warning! " << idx << "parameter don't have Bind Member!" << std::endl;
		};
	(lambda(args), ...);

}





