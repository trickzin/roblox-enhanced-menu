#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include <string>
#include <vector>
#include <map>

struct OptimizationSettings {
    bool texturesOptimized;
    bool graphicsMinimized;
    bool effectsReduced;
    bool shadowsDisabled;
    bool lightingReduced;
    bool viewDistanceReduced;
    int targetFPS;
    
    OptimizationSettings()
        : texturesOptimized(false)
        , graphicsMinimized(false)
        , effectsReduced(false)
        , shadowsDisabled(false)
        , lightingReduced(false)
        , viewDistanceReduced(false)
        , targetFPS(60)
    {}
};

class OptimizationManager {
public:
    OptimizationManager();
    ~OptimizationManager();

    void ApplyAllOptimizations();
    void ApplyQuickOptimizations();
    void RestoreDefaults();
    void CleanTextures();
    void SetGraphicsToMinimum();
    void ReduceParticleEffects();
    void DisableShadows();
    void ReduceLighting();
    void ReduceViewDistance();

    bool AreTexturesOptimized() const { return m_settings.texturesOptimized; }
    bool AreGraphicsMinimized() const { return m_settings.graphicsMinimized; }
    bool AreEffectsReduced() const { return m_settings.effectsReduced; }
    bool AreShadowsDisabled() const { return m_settings.shadowsDisabled; }

    void SetTargetFPS(int fps) { m_settings.targetFPS = fps; }
    int GetTargetFPS() const { return m_settings.targetFPS; }
    
    const OptimizationSettings& GetSettings() const { return m_settings; }

private:
    void OptimizeRobloxGraphics();
    void OptimizeSystemPerformance();
    void ApplyGraphicsSettings();
    void CleanupMemory();    
    void LogOptimization(const std::string& action);
    
    OptimizationSettings m_settings;
    OptimizationSettings m_defaultSettings;
    
    std::vector<std::string> m_optimizationLog;
    
    float m_preOptimizationFPS;
    float m_postOptimizationFPS;
};

#endif
