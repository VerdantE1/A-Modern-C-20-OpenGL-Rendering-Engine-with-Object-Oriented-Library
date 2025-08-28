#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Utility.h"
#include "DrawDemo.h"
#include "SolarSystem.h"
#include "Globals.h"
#include "Logger.h"

#include "spdlog/spdlog.h"

int main(void)
{
    // 在程序开始时初始化日志系统
    Logger::Initialize();
    LOG_START();

    LOG_SECTION("初始化");
    

    LOG_LEVEL_INFO(0, "开始 GLFW 初始化");
    if (!glfwInit()) {
        LOG_LEVEL_ERROR(1, "GLFW 初始化失败");
        return -1;
    }
    LOG_LEVEL_INFO(1, "GLFW 初始化成功");

    LOG_LEVEL_INFO(0, "配置 OpenGL 上下文");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    LOG_LEVEL_INFO(1, "OpenGL 版本: 3.3 Core Profile");

    LOG_LEVEL_INFO(0, "创建窗口");
    GLFWwindow* window = glfwCreateWindow(2560, 1660, "Hello World", NULL, NULL);
    if (!window) {
        LOG_LEVEL_ERROR(1, "窗口创建失败");
        glfwTerminate();
        return -1;
    }
    LOG_LEVEL_INFO(1, "窗口创建成功: 2560x1660");

    LOG_LEVEL_INFO(0, "设置 OpenGL 上下文");
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    LOG_LEVEL_INFO(1, "上下文设置完成，VSync 已启用");

    LOG_LEVEL_INFO(0, "初始化 GLEW");
    if (glewInit() != GLEW_OK) {
        LOG_LEVEL_ERROR(1, "GLEW 初始化失败");
        return -1;
    }
    LOG_LEVEL_INFO(1, "GLEW 初始化成功");
    LOG_LEVEL_INFO(1, "OpenGL 版本: {}", (const char*)glGetString(GL_VERSION));

    LOG_SECTION("主渲染");
    LOG_LEVEL_INFO(0, "启动阴影映射与 ECS");
    DrawShadowMappingWithECS(window);
    LOG_LEVEL_INFO(0, "渲染完成");

    LOG_SECTION("清理");
    LOG_LEVEL_INFO(0, "终止 GLFW");
    glfwTerminate();

    Logger::Shutdown();
    return 0;
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
