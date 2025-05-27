#ifndef MENU_H
#define MENU_H

#include "imgui.h"
#include <vector>
#include <string>
#include <map>
#include <memory>
#include "performance_monitor.h"
#include "optimization.h"
#include "themes.h"

struct ToggleFeature {
    std::string name;
    std::string description;
    bool enabled;
    std::string category;
    
    ToggleFeature(const std::string& n, const std::string& desc, const std::string& cat)
        : name(n), description(desc), enabled(false), category(cat) {}
};

class RobloxMenu {
public:
    RobloxMenu();
    ~RobloxMenu();

    void Initialize();
    void Shutdown();
    void Update();
    void Render();

private:
    void RenderMainMenuBar();
    void RenderCreditsSection();
    void RenderFeaturesSection();
    void RenderCustomizationSection();
    void RenderPerformanceSection();
    void RenderOptimizationSection();
    void RenderAboutSection();
    void SetupStyle();
    void HandleResponsiveDesign();
    void UpdateRGBAnimation();
    void SaveConfiguration();
    void LoadConfiguration();

    bool m_showMenu;
    bool m_showCredits;
    bool m_showFeatures;
    bool m_showCustomization;
    bool m_showPerformance;
    bool m_showOptimization;
    bool m_showAbout;
    bool m_rgbMode;
    ImVec4 m_baseColor;
    float m_rgbTimer;
    float m_menuAlpha;
    float m_roundingAmount;
    
    std::vector<ToggleFeature> m_features;
    std::map<std::string, std::vector<int>> m_featureCategories;
    std::unique_ptr<PerformanceMonitor> m_performanceMonitor;
    std::unique_ptr<OptimizationManager> m_optimizationManager;
    std::unique_ptr<ThemeManager> m_themeManager;

    ImVec2 m_windowSize;
    ImVec2 m_windowPos;
    bool m_isMinimized;
    bool m_isMobileDevice;
    float m_scaleFactor;
    float m_fadeTimer;
    float m_pulseTimer;
};

#endif
