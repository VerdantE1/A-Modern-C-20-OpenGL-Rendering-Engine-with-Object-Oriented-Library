#pragma once
/*
* Resource means the OpenGl give you a resource,So the m_id is the handle given by OpenGl
*/
class Resource
{
public:

	
	Resource() :m_id(0) {}	
	Resource(unsigned int id) : m_id(id) {};

	//Prevent copying
	Resource(const Resource& other) = delete;
	Resource& operator=(const Resource& other) = delete;

	// Could be move
	Resource(Resource&& other);
	Resource& operator=(Resource&& other);

	virtual ~Resource() = default;

	unsigned int GetID() const { return m_id; } // Returns the resource ID
	virtual void Bind() const = 0; // Bind the resource to the current context
	virtual void Unbind() const = 0; // Unbind the resource from the current context
	
	
	
protected:
	unsigned int m_id; 
	
};


inline Resource::Resource(Resource&& other)
	: m_id(other.m_id)
{
	other.m_id = 0;
}

inline Resource& Resource:: operator=(Resource&& other)
{
	if (this != &other)
	{
		m_id = other.m_id;
		other.m_id = 0;
	}
	return *this;
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
