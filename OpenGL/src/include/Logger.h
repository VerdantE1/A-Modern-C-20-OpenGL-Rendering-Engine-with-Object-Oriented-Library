#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>
#include <filesystem>
#include <string>

// 便捷宏定义
#define LOG_TRACE(...)    spdlog::trace(__VA_ARGS__)
#define LOG_DEBUG(...)    spdlog::debug(__VA_ARGS__)
#define LOG_INFO(...)     spdlog::info(__VA_ARGS__)
#define LOG_WARN(...)     spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...)    spdlog::error(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)

class Logger {
public:
    static void Initialize() {
        // 创建 logs 目录（如果不存在）
        std::filesystem::create_directories("logs");
        
        // 创建控制台输出 sink
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("[%H:%M:%S.%e] [%^%l%$] %v");
        
        // 创建旋转文件 sink
        // 参数：文件路径, 单个文件大小(5MB), 保留文件数量(20)
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            "logs/opengl.log", 1024 * 1024 * 5, 20);
        file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%s:%#] %v");
        
        // 将多个 sink 组合到一个 logger 中
        std::vector<spdlog::sink_ptr> sinks { console_sink, file_sink };
        auto logger = std::make_shared<spdlog::logger>("multi_sink", sinks.begin(), sinks.end());
        
        // 设置日志级别
        logger->set_level(spdlog::level::debug);
        
        // 设置刷新策略：警告级别以上立即刷新
        logger->flush_on(spdlog::level::warn);
        
        // 注册为默认 logger
        spdlog::register_logger(logger);
        spdlog::set_default_logger(logger);
        
        LOG_INFO("=== Logger initialized successfully ===");
        LOG_INFO("Log files will be saved to: logs/opengl.log");
        LOG_INFO("Keeping latest 20 log files with 5MB each");
    }
    
    static void Shutdown() {
        LOG_INFO("=== Logger shutting down ===");
        spdlog::shutdown();
    }

    // 手动刷新所有日志到文件
    static void Flush() {
        spdlog::default_logger()->flush();
    }
    
    // 设置日志级别
    static void SetLevel(spdlog::level::level_enum level) {
        spdlog::default_logger()->set_level(level);
    }
};



// OpenGL 专用宏
#define LOG_GL_ERROR(msg) \
    do { \
        GLenum err = glGetError(); \
        if (err != GL_NO_ERROR) { \
            LOG_ERROR("OpenGL Error: {} - {}", err, msg); \
        } \
    } while(0)

// 带条件的日志宏
#define LOG_IF(condition, level, ...) \
    do { \
        if (condition) { \
            LOG_##level(__VA_ARGS__); \
        } \
    } while(0)

// 性能计时宏
#define LOG_TIMER_START(name) \
    auto timer_##name##_start = std::chrono::high_resolution_clock::now()

#define LOG_TIMER_END(name) \
    do { \
        auto timer_##name##_end = std::chrono::high_resolution_clock::now(); \
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( \
            timer_##name##_end - timer_##name##_start).count(); \
        LOG_DEBUG("Timer '{}' took {} ms", #name, duration); \
    } while(0)
