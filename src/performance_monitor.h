#ifndef PERFORMANCE_MONITOR_H
#define PERFORMANCE_MONITOR_H

#include <chrono>
#include <vector>
#include <memory>

class PerformanceMonitor {
public:
    PerformanceMonitor();
    ~PerformanceMonitor();

    void Initialize();
    void Shutdown();
    void Update();

    float GetFPS() const { return m_currentFPS; }
    float GetFrameTime() const { return m_frameTime; }
    float GetCPUUsage() const { return m_cpuUsage; }
    float GetMemoryUsage() const { return m_memoryUsage; }
    int GetPing() const { return m_ping; }

    const std::vector<float>& GetFPSHistory() const { return m_fpsHistory; }
    const std::vector<float>& GetCPUHistory() const { return m_cpuHistory; }

private:
    void UpdateFPS();
    void UpdateCPUUsage();
    void UpdateMemoryUsage();
    void UpdateNetworkLatency();

    float GetSystemCPUUsage();
    float GetSystemMemoryUsage();
    int GetNetworkPing();

    float m_currentFPS;
    float m_frameTime;
    float m_cpuUsage;
    float m_memoryUsage;
    int m_ping;

    std::chrono::high_resolution_clock::time_point m_lastFrameTime;
    std::chrono::high_resolution_clock::time_point m_lastUpdateTime;
    
    int m_frameCount;
    std::chrono::high_resolution_clock::time_point m_fpsCountStartTime;

    std::vector<float> m_fpsHistory;
    std::vector<float> m_cpuHistory;
    std::vector<float> m_memoryHistory;
    
    float m_cpuUpdateInterval;
    float m_memoryUpdateInterval;
    float m_pingUpdateInterval;    
    float m_cpuUpdateTimer;
    float m_memoryUpdateTimer;
    float m_pingUpdateTimer;

    static const size_t MAX_HISTORY_SIZE = 100;
};

#endif
