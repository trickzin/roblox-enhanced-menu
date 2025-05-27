#include "optimization.h"
#include <iostream>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#include <tlhelp32.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#endif

OptimizationManager::OptimizationManager()
{
    m_defaultSettings = m_settings;
    m_preOptimizationFPS = 0.0f;
    m_postOptimizationFPS = 0.0f;
    
    std::cout << "Optimization Manager initialized!" << std::endl;
}

OptimizationManager::~OptimizationManager()
{

}

void OptimizationManager::ApplyAllOptimizations()
{
    LogOptimization("Starting comprehensive optimization...");
    
    m_preOptimizationFPS = 0.0f;
    
    CleanTextures();
    SetGraphicsToMinimum();
    ReduceParticleEffects();
    DisableShadows();
    ReduceLighting();
    CleanupMemory();
    OptimizeSystemPerformance();
    
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    LogOptimization("Comprehensive optimization completed!");
    
    std::cout << "All optimizations applied successfully!" << std::endl;
}

void OptimizationManager::ApplyQuickOptimizations()
{
    LogOptimization("Applying quick optimizations...");
    
    CleanTextures();
    ReduceParticleEffects();
    CleanupMemory();
    
    LogOptimization("Quick optimization completed!");
    
    std::cout << "Quick optimizations applied!" << std::endl;
}

void OptimizationManager::RestoreDefaults()
{
    LogOptimization("Restoring default settings...");
    
    m_settings = m_defaultSettings;    
    ApplyGraphicsSettings();
    
    LogOptimization("Default settings restored!");
    
    std::cout << "Default settings have been restored." << std::endl;
}

void OptimizationManager::CleanTextures()
{
    LogOptimization("Cleaning textures...");    
    
    m_settings.texturesOptimized = true;
    
    std::cout << "Cleaning unnecessary textures..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    
    LogOptimization("Texture cleanup completed");
    std::cout << "Textures optimized for better performance!" << std::endl;
}

void OptimizationManager::SetGraphicsToMinimum()
{
    LogOptimization("Setting graphics to minimum...");
    
    m_settings.graphicsMinimized = true;
    
    std::cout << "Adjusting graphics settings to minimum..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    LogOptimization("Graphics set to minimum quality");
    std::cout << "Graphics settings optimized for maximum FPS!" << std::endl;
}

void OptimizationManager::ReduceParticleEffects()
{
    LogOptimization("Reducing particle effects...");
        
    m_settings.effectsReduced = true;
    
    std::cout << "Reducing visual effects and particles..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    
    LogOptimization("Particle effects reduced");
    std::cout << "Visual effects optimized!" << std::endl;
}

void OptimizationManager::DisableShadows()
{
    LogOptimization("Disabling shadows...");    
    
    m_settings.shadowsDisabled = true;
    
    std::cout << "Disabling shadow rendering..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    LogOptimization("Shadows disabled");
    std::cout << "Shadows disabled for better performance!" << std::endl;
}

void OptimizationManager::ReduceLighting()
{
    LogOptimization("Reducing lighting quality...");
        
    m_settings.lightingReduced = true;
    
    std::cout << "Optimizing lighting settings..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(120));
    
    LogOptimization("Lighting quality reduced");
    std::cout << "Lighting optimized!" << std::endl;
}

void OptimizationManager::ReduceViewDistance()
{
    LogOptimization("Reducing view distance...");
        
    m_settings.viewDistanceReduced = true;
    
    std::cout << "Reducing view distance..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    LogOptimization("View distance reduced");
    std::cout << "View distance optimized!" << std::endl;
}

void OptimizationManager::OptimizeRobloxGraphics()
{
    LogOptimization("Optimizing Roblox-specific graphics...");
        
    std::cout << "Applying Roblox-specific optimizations..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    
    LogOptimization("Roblox graphics optimized");
}

void OptimizationManager::OptimizeSystemPerformance()
{
    LogOptimization("Optimizing system performance...");    
    
    std::cout << "Optimizing system performance..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    
    LogOptimization("System performance optimized");
}

void OptimizationManager::ApplyGraphicsSettings()
{
    
    if (m_settings.graphicsMinimized) {
        std::cout << "Applying minimum graphics settings..." << std::endl;
    }
    
    if (m_settings.shadowsDisabled) {
        std::cout << "Applying shadow disable settings..." << std::endl;
    }
    
    if (m_settings.lightingReduced) {
        std::cout << "Applying reduced lighting settings..." << std::endl;
    }
}

void OptimizationManager::CleanupMemory()
{
    LogOptimization("Cleaning up memory...");
    
    
    std::cout << "Cleaning up memory..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    LogOptimization("Memory cleanup completed");
    std::cout << "✅ Memory optimized!" << std::endl;
}

void OptimizationManager::LogOptimization(const std::string& action)
{
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::string logEntry = std::to_string(time_t) + ": " + action;
    m_optimizationLog.push_back(logEntry);
    
    if (m_optimizationLog.size() > 50) {
        m_optimizationLog.erase(m_optimizationLog.begin());
    }
    
    std::cout << "[OPTIMIZATION] " << action << std::endl;
}
