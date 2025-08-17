#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "IndexBuffer.h"



class Renderer;

class Shaper {
public:
    //verticesSizeÊÇ×Ö½ÚÊý£¬
    Shaper(const void* vertices,unsigned int verticesSize, const unsigned int* indices, unsigned int indicesSize, std::vector<VertexBufferLayout::SupportedTypes> acnt_vec)
        : vb(vertices, verticesSize), ib(indices,indicesSize),layout(acnt_vec)
    {
        va.LinkBufferAndLayout(vb, layout);
    }
    virtual ~Shaper() = default;
    virtual void Draw(Shader& shader, const Renderer& renderer) = 0;

    const VertexArray& GetVertexArray() const { return va; }
	const VertexBuffer& GetVertexBuffer() const { return vb; }
    const IndexBuffer& GetIndexBuffer() const { return ib; }
	const VertexBufferLayout& GetVertexBufferLayout() const { return layout; }

protected:
    VertexArray va;
    VertexBuffer vb;
    IndexBuffer ib;
    VertexBufferLayout layout;
};
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
