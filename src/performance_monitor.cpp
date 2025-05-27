#include "performance_monitor.h"
#include <iostream>
#include <algorithm>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#include <pdh.h>
#pragma comment(lib, "pdh.lib")
#pragma comment(lib, "psapi.lib")
#else
#include <sys/times.h>
#include <sys/vtimes.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <fstream>
#endif

PerformanceMonitor::PerformanceMonitor()
    : m_currentFPS(60.0f)
    , m_frameTime(16.67f)
    , m_cpuUsage(0.0f)
    , m_memoryUsage(0.0f)
    , m_ping(50)
    , m_frameCount(0)
    , m_cpuUpdateInterval(1.0f) 
    , m_memoryUpdateInterval(2.0f) 
    , m_pingUpdateInterval(5.0f) 
    , m_cpuUpdateTimer(0.0f)
    , m_memoryUpdateTimer(0.0f)
    , m_pingUpdateTimer(0.0f)
{

    m_fpsHistory.resize(MAX_HISTORY_SIZE, 60.0f);
    m_cpuHistory.resize(MAX_HISTORY_SIZE, 0.0f);
    m_memoryHistory.resize(MAX_HISTORY_SIZE, 0.0f);
}

PerformanceMonitor::~PerformanceMonitor()
{
    Shutdown();
}

void PerformanceMonitor::Initialize()
{
    m_lastFrameTime = std::chrono::high_resolution_clock::now();
    m_lastUpdateTime = m_lastFrameTime;
    m_fpsCountStartTime = m_lastFrameTime;

    std::cout << "Performance Monitor initialized successfully!" << std::endl;
}

void PerformanceMonitor::Shutdown()
{
    std::cout << "Performance Monitor shutdown complete." << std::endl;
}

void PerformanceMonitor::Update()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    
    UpdateFPS();
    
    float deltaTime = std::chrono::duration<float>(currentTime - m_lastUpdateTime).count();
    m_lastUpdateTime = currentTime;
    
    m_cpuUpdateTimer += deltaTime;
    m_memoryUpdateTimer += deltaTime;
    m_pingUpdateTimer += deltaTime;
    
    if (m_cpuUpdateTimer >= m_cpuUpdateInterval) {
        UpdateCPUUsage();
        m_cpuUpdateTimer = 0.0f;
    }
    
    if (m_memoryUpdateTimer >= m_memoryUpdateInterval) {
        UpdateMemoryUsage();
        m_memoryUpdateTimer = 0.0f;
    }
    
    if (m_pingUpdateTimer >= m_pingUpdateInterval) {
        UpdateNetworkLatency();
        m_pingUpdateTimer = 0.0f;
    }
}

void PerformanceMonitor::UpdateFPS()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    
    float frameTime = std::chrono::duration<float, std::milli>(currentTime - m_lastFrameTime).count();
    m_frameTime = frameTime;
    m_lastFrameTime = currentTime;
    m_frameCount++;
    
    float timeSinceLastFPSUpdate = std::chrono::duration<float>(currentTime - m_fpsCountStartTime).count();
    if (timeSinceLastFPSUpdate >= 1.0f) {
        m_currentFPS = static_cast<float>(m_frameCount) / timeSinceLastFPSUpdate;
        
        m_fpsHistory.erase(m_fpsHistory.begin());
        m_fpsHistory.push_back(m_currentFPS);       
        m_frameCount = 0;
        m_fpsCountStartTime = currentTime;
    }
}

void PerformanceMonitor::UpdateCPUUsage()
{
    m_cpuUsage = GetSystemCPUUsage();    
    m_cpuHistory.erase(m_cpuHistory.begin());
    m_cpuHistory.push_back(m_cpuUsage);
}

void PerformanceMonitor::UpdateMemoryUsage()
{
    m_memoryUsage = GetSystemMemoryUsage();    
    m_memoryHistory.erase(m_memoryHistory.begin());
    m_memoryHistory.push_back(m_memoryUsage);
}

void PerformanceMonitor::UpdateNetworkLatency()
{
    m_ping = GetNetworkPing();
}

float PerformanceMonitor::GetSystemCPUUsage()
{
#ifdef _WIN32
    static PDH_HQUERY cpuQuery;
    static PDH_HCOUNTER cpuTotal;
    static bool initialized = false;
    
    if (!initialized) {
        PdhOpenQuery(NULL, NULL, &cpuQuery);
        PdhAddEnglishCounter(cpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal);
        PdhCollectQueryData(cpuQuery);
        initialized = true;
        return 0.0f;
    }
    
    PDH_FMT_COUNTERVALUE counterVal;
    PdhCollectQueryData(cpuQuery);
    PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_DOUBLE, NULL, &counterVal);
    
    return static_cast<float>(counterVal.doubleValue);
#else
    static long long lastTotalUser = 0, lastTotalUserLow = 0, lastTotalSys = 0, lastTotalIdle = 0;
    
    std::ifstream file("/proc/stat");
    if (!file.is_open()) {
        return 0.0f;
    }
    
    std::string line;
    std::getline(file, line);
    file.close();
    
    long long totalUser, totalUserLow, totalSys, totalIdle, total;
    sscanf(line.c_str(), "cpu %lld %lld %lld %lld", &totalUser, &totalUserLow, &totalSys, &totalIdle);
    
    if (lastTotalUser == 0) {
        lastTotalUser = totalUser;
        lastTotalUserLow = totalUserLow;
        lastTotalSys = totalSys;
        lastTotalIdle = totalIdle;
        return 0.0f;
    }
    
    total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) + (totalSys - lastTotalSys);
    float percent = total;
    total += (totalIdle - lastTotalIdle);
    percent /= total;
    percent *= 100;
    
    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;
    
    return percent;
#endif
}

float PerformanceMonitor::GetSystemMemoryUsage()
{
#ifdef _WIN32
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    
    DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
    DWORDLONG physMemUsed = memInfo.ullTotalPhys - memInfo.ullAvailPhys;
    
    return (static_cast<float>(physMemUsed) / static_cast<float>(totalPhysMem)) * 100.0f;
#else
    struct sysinfo memInfo;
    sysinfo(&memInfo);
    
    long long totalPhysMem = memInfo.totalram;
    totalPhysMem *= memInfo.mem_unit;
    
    long long physMemUsed = memInfo.totalram - memInfo.freeram;
    physMemUsed *= memInfo.mem_unit;
    
    return (static_cast<float>(physMemUsed) / static_cast<float>(totalPhysMem)) * 100.0f;
#endif
}

int PerformanceMonitor::GetNetworkPing()
{
    
    static int basePing = 45;
    static float pingTimer = 0.0f;
    
    pingTimer += 0.1f;
    
    int variation = static_cast<int>(sinf(pingTimer) * 15.0f);
    int currentPing = basePing + variation;
    
    return std::max(10, std::min(200, currentPing));
}
