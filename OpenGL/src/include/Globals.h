#pragma once
#include "Light/Utils.h"
/******************************************* 全局窗口变量  *************************************************/
inline int g_WindowWidth = 0;
inline int g_WindowHeight = 0;

/******************************************* 光照参数相关变量  *************************************************/

// 光照相关的uniform位置
inline GLuint globalAmbLoc = 0;	   
inline GLuint ambLoc = 0;
inline GLuint diffLoc = 0;
inline GLuint specLoc = 0;
inline GLuint posLoc = 0;
inline GLuint mAmbLoc = 0;            
inline GLuint mDiffLoc = 0;          
inline GLuint mSpecLoc = 0;           
inline GLuint mShineLoc = 0;          

// 光源属性
// 位置position（x, y, z）
inline glm::vec3 initialLightLoc(5.0f, 2.0f, 2.0f); // 初始光源位置（模型空间）
inline glm::vec3 currentLightPos;		// 光源位置（模型空间）
inline glm::vec3 lightPosV;			// 变换到视图空间后的光源位置
inline float lightPos[3];				// 传递给GLSL的光源位置数组

// 光照颜色属性
inline float globalAmbient[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
inline float lightAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
inline float lightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
inline float lightSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };	

inline float* matAmb = goldAmbient();   // 物体材质环境光
inline float* matDif = goldDiffuse();   // 物体材质漫反射
inline float* matSpe = goldSpecular();  // 物体材质镜面反射
inline float matShi = goldShininess();    // 物体材质高光系数

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
