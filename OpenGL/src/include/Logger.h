#pragma once
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <memory>
#include <filesystem>
#include <string>

// 定义颜色宏
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define BLUE	"\033[34m"



// 便捷宏定义
#define LOG_TRACE(...)    spdlog::trace(__VA_ARGS__)
#define LOG_DEBUG(...)    spdlog::debug(__VA_ARGS__)
#define LOG_INFO(...)     spdlog::info(__VA_ARGS__)
#define LOG_WARN(...)     spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...)    spdlog::error(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)

// 自定义日志宏
#define LOG_SUCCESS(message, ...) \
    spdlog::info(GREEN message RESET, ##__VA_ARGS__)

#define LOG_WARNING(message, ...) \
    spdlog::warn(YELLOW message RESET, ##__VA_ARGS__)

#define LOG_FAILED(message, ...) \
    spdlog::error(RED message RESET, ##__VA_ARGS__)

// 新增宏定义
#define LOG_START()       Logger::LogStart()
#define LOG_SECTION(name) Logger::LogSection(name)


// 辅助函数: 计算两个字符串的总长度
constexpr size_t Strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        ++len;
    }
    return len;
}
template<size_t N1, size_t N2>
constexpr auto ConcatStrings(const char (& str1)[N1], const char (& str2)[N2]) {
    constexpr std::array<char, N1 + N2 - 1> result{};  // N1 和 N2 都包含 '\0'，所以减 1
    for (size_t i = 0; i < N1 - 1; ++i) {
        result[i] = str1[i];  // 复制 str1
    }
    for (size_t i = 0; i < N2; ++i) {
        result[N1 - 1 + i] = str2[i];  // 复制 str2，包括 '\0'
    }
    return result;
}

class Logger {
private:
    static inline int s_indentLevel = 0;
    static std::string GetIndent(int level = -1) {
        int actualLevel = (level == -1) ? s_indentLevel : level;
        return std::string(actualLevel, '\t'); // 使用 Tab 字符
    }
    
    // 简单的编译时缩进字符串
    static constexpr const char* GetIndentString(int level) {
        switch (level) {
        case 0: return "";
        case 1: return "\t";
        case 2: return "\t\t";
        case 3: return "\t\t\t";
        case 4: return "\t\t\t\t";
        case 5: return "\t\t\t\t\t";
        default: return "\t\t\t\t\t"; // 最多5级
        }
    }


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

    // 应用程序启动标志
    static void LogStart() {
        LOG_INFO("════════════════════════════════════════");
        LOG_INFO("        APPLICATION STARTED");
        LOG_INFO("════════════════════════════════════════");
    }

    // 模块/区段开始标志
    static void LogSection(const std::string& sectionName) {
        LOG_INFO("═════════════════════════════════════════");
        LOG_INFO("SECTION: {}", sectionName);
        LOG_INFO("═════════════════════════════════════════");
    }


    //层级日志函数 - 支持无参数情况
    static void LogWithLevel(int level, spdlog::level::level_enum logLevel, const char* fmt) 
    {
        std::string indentedFormat = GetIndent(level) + std::string(fmt);
        spdlog::default_logger()->log(logLevel, indentedFormat);
    }
    




    // 增加/减少缩进层级
    static void IncreaseIndent() { s_indentLevel++; }
    static void DecreaseIndent() { if (s_indentLevel > 0) s_indentLevel--; }
    static void ResetIndent() { s_indentLevel = 0; }
    static int GetCurrentIndent() { return s_indentLevel; }

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

// 层级日志宏
#define LOG_LEVEL_TRACE(_level, fmt, ...) \
    Logger::LogWithLevel(_level, spdlog::level::trace, fmt)

#define LOG_LEVEL_DEBUG(_level, fmt, ...) \
    Logger::LogWithLevel(_level, spdlog::level::debug, fmt)

#define LOG_LEVEL_INFO(_level, fmt, ...) \
    Logger::LogWithLevel(_level, spdlog::level::info, fmt)

#define LOG_LEVEL_WARN(_level, fmt, ...) \
    Logger::LogWithLevel(_level, spdlog::level::warn, fmt)

#define LOG_LEVEL_ERROR(_level, fmt, ...) \
    Logger::LogWithLevel(_level, spdlog::level::err, fmt)





#define LOG_LEVEL_INFO_W(_level, fmt, ...) \
    Logger::LogWithLevel(_level, spdlog::level::info, fmt, ##__VA_ARGS__)

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
