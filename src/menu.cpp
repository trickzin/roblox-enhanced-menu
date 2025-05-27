#include "menu.h"
#include "imgui.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

RobloxMenu::RobloxMenu()
    : m_showMenu(true)
    , m_showCredits(true)
    , m_showFeatures(true)
    , m_showCustomization(false)
    , m_showPerformance(true)
    , m_showOptimization(false)
    , m_showAbout(false)
    , m_rgbMode(false)
    , m_baseColor(0.2f, 0.4f, 0.8f, 1.0f)
    , m_rgbTimer(0.0f)
    , m_menuAlpha(0.95f)
    , m_roundingAmount(8.0f)
    , m_windowSize(800, 600)
    , m_windowPos(100, 100)
    , m_isMinimized(false)
    , m_isMobileDevice(false)
    , m_scaleFactor(1.0f)
    , m_fadeTimer(0.0f)
    , m_pulseTimer(0.0f)
{
}

RobloxMenu::~RobloxMenu()
{
    Shutdown();
}

void RobloxMenu::Initialize()
{
    m_performanceMonitor = std::make_unique<PerformanceMonitor>();
    m_optimizationManager = std::make_unique<OptimizationManager>();
    m_themeManager = std::make_unique<ThemeManager>();

    m_performanceMonitor->Initialize();
    m_features.clear();    
    m_features.emplace_back("Player ESP", "Show player outlines and information", "ESP");
    m_features.emplace_back("Item ESP", "Highlight important items", "ESP");
    m_features.emplace_back("Distance ESP", "Show distance to players/items", "ESP");    
    m_features.emplace_back("Speed Boost", "Increase movement speed", "Movement");
    m_features.emplace_back("Jump Boost", "Enhanced jumping ability", "Movement");
    m_features.emplace_back("No Clip", "Walk through walls", "Movement");
    m_features.emplace_back("Fly Mode", "Flying capability", "Movement");    
    m_features.emplace_back("Aimbot", "Automatic aiming assistance", "Combat");
    m_features.emplace_back("Auto Attack", "Automatic attacking", "Combat");
    m_features.emplace_back("Damage Boost", "Increased damage output", "Combat");    
    m_features.emplace_back("Auto Farm", "Automatic resource collection", "Utility");
    m_features.emplace_back("Teleport", "Instant location change", "Utility");
    m_features.emplace_back("God Mode", "Invincibility mode", "Utility");
    m_featureCategories.clear();
    for (size_t i = 0; i < m_features.size(); ++i) {
        m_featureCategories[m_features[i].category].push_back(static_cast<int>(i));
    }
    ImGuiIO& io = ImGui::GetIO();
    m_isMobileDevice = io.ConfigFlags & ImGuiConfigFlags_IsTouchScreen;
    m_scaleFactor = m_isMobileDevice ? 1.5f : 1.0f;

    LoadConfiguration();

    std::cout << "Roblox Enhanced Menu initialized successfully!" << std::endl;
}

void RobloxMenu::Shutdown()
{
    SaveConfiguration();

    if (m_performanceMonitor) {
        m_performanceMonitor->Shutdown();
        m_performanceMonitor.reset();
    }
    
    if (m_optimizationManager) {
        m_optimizationManager.reset();
    }
    
    if (m_themeManager) {
        m_themeManager.reset();
    }

    std::cout << "Roblox Enhanced Menu shutdown complete." << std::endl;
}

void RobloxMenu::Update()
{
    m_rgbTimer += ImGui::GetIO().DeltaTime;
    m_fadeTimer += ImGui::GetIO().DeltaTime;
    m_pulseTimer += ImGui::GetIO().DeltaTime;

    if (m_rgbMode) {
        UpdateRGBAnimation();
    }

    if (m_performanceMonitor) {
        m_performanceMonitor->Update();
    }

    HandleResponsiveDesign();
}

void RobloxMenu::Render()
{
    if (!m_showMenu) return;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;
    
    if (m_isMobileDevice) {
        window_flags |= ImGuiWindowFlags_NoResize;
    }

    SetupStyle();

    ImGui::SetNextWindowSize(m_windowSize, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(m_windowPos, ImGuiCond_FirstUseEver);

    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, m_menuAlpha);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, m_roundingAmount);
    
    if (ImGui::Begin("Roblox Enhanced Menu v1.0", &m_showMenu, window_flags)) {
        
        m_windowSize = ImGui::GetWindowSize();
        m_windowPos = ImGui::GetWindowPos();

        RenderMainMenuBar();

        if (ImGui::BeginTabBar("MenuTabs", ImGuiTabBarFlags_Reorderable)) {
            
            if (ImGui::BeginTabItem("Credits")) {
                RenderCreditsSection();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Features")) {
                RenderFeaturesSection();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Performance")) {
                RenderPerformanceSection();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Optimization")) {
                RenderOptimizationSection();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Customization")) {
                RenderCustomizationSection();
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("About")) {
                RenderAboutSection();
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
    }
    ImGui::End();
    
    ImGui::PopStyleVar(2);
}

void RobloxMenu::RenderMainMenuBar()
{
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Save Config")) {
                SaveConfiguration();
            }
            if (ImGui::MenuItem("Load Config")) {
                LoadConfiguration();
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) {
                m_showMenu = false;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View")) {
            ImGui::MenuItem("Credits", nullptr, &m_showCredits);
            ImGui::MenuItem("Features", nullptr, &m_showFeatures);
            ImGui::MenuItem("Performance", nullptr, &m_showPerformance);
            ImGui::MenuItem("Optimization", nullptr, &m_showOptimization);
            ImGui::MenuItem("Customization", nullptr, &m_showCustomization);
            ImGui::EndMenu();
        }

        if (m_performanceMonitor) {
            float fps = m_performanceMonitor->GetFPS();
            ImGui::Separator();
            ImGui::Text("FPS: %.1f", fps);
            
            if (fps >= 60.0f) {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "●");
            } else if (fps >= 30.0f) {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "●");
            } else {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "●");
            }
        }

        ImGui::EndMenuBar();
    }
}

void RobloxMenu::RenderCreditsSection()
{
    float pulse = 1.0f + 0.1f * sinf(m_pulseTimer * 3.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, pulse);
    
    ImVec2 windowSize = ImGui::GetWindowSize();
    const char* title = "ROBLOX ENHANCED MENU";
    ImVec2 textSize = ImGui::CalcTextSize(title);
    ImGui::SetCursorPosX((windowSize.x - textSize.x) * 0.5f);
    
    if (m_rgbMode) {
        ImGui::TextColored(ImVec4(m_baseColor.x, m_baseColor.y, m_baseColor.z, 1.0f), title);
    } else {
        ImGui::TextColored(ImVec4(0.3f, 0.7f, 1.0f, 1.0f), title);
    }
    
    ImGui::PopStyleVar();
    
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f, 0.0f, 1.0f));
    ImGui::Text("Created by: trickzqww");
    ImGui::PopStyleColor();
    
    ImGui::Text("Contact: sintofaltadela@gmail.com");
    ImGui::Text("🌐 Website: https://trickzin.github.io/trick-little-man/");
    ImGui::Text("Version: 0.0.1 - Release Date: 2025");
    
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.5f, 1.0f), "Key Features:");
    ImGui::BulletText("Advanced ESP and Visual Enhancements");
    ImGui::BulletText("Movement and Combat Modifications");
    ImGui::BulletText("Real-time Performance Monitoring");
    ImGui::BulletText("FPS Optimization Tools");
    ImGui::BulletText("Fully Customizable Interface");
    ImGui::BulletText("Mobile and PC Compatible");

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "Special Thanks:");
    ImGui::BulletText("Dear ImGui Team for the amazing UI framework");
    ImGui::BulletText("Roblox Community for inspiration and feedback");
    ImGui::BulletText("Beta testers for valuable input");

    ImGui::Spacing();
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
    ImGui::TextWrapped("⚠️ DISCLAIMER: This software is for educational purposes only. "
                      "Use responsibly and in accordance with Roblox Terms of Service.");
    ImGui::PopStyleColor();
}

void RobloxMenu::RenderFeaturesSection()
{
    ImGui::Text("Feature Control Panel");
    ImGui::Separator();

    static char searchBuffer[256] = "";
    ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.3f);
    ImGui::InputTextWithHint("##search", "Search features...", searchBuffer, sizeof(searchBuffer));
    
    ImGui::SameLine();
    if (ImGui::Button("Enable All")) {
        for (auto& feature : m_features) {
            feature.enabled = true;
        }
    }
    
    ImGui::SameLine();
    if (ImGui::Button("Disable All")) {
        for (auto& feature : m_features) {
            feature.enabled = false;
        }
    }

    ImGui::Spacing();

    for (const auto& category : m_featureCategories) {
        const std::string& categoryName = category.first;
        const std::vector<int>& featureIndices = category.second;

        std::string headerText = " " + categoryName + " Features";
        if (ImGui::CollapsingHeader(headerText.c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
            
            ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 20.0f);
            
            for (int index : featureIndices) {
                ToggleFeature& feature = m_features[index];
                
                std::string searchStr = searchBuffer;
                std::transform(searchStr.begin(), searchStr.end(), searchStr.begin(), ::tolower);
                std::string featureName = feature.name;
                std::transform(featureName.begin(), featureName.end(), featureName.begin(), ::tolower);
                
                if (!searchStr.empty() && featureName.find(searchStr) == std::string::npos) {
                    continue;
                }

                ImGui::TreePush(feature.name.c_str());

                bool wasEnabled = feature.enabled;
                
                if (feature.enabled) {
                    ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
                    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.3f, 0.0f, 0.5f));
                } else {
                    ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
                    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.2f, 0.2f, 0.5f));
                }

                ImGui::Checkbox(("##" + feature.name).c_str(), &feature.enabled);
                ImGui::PopStyleColor(2);

                ImGui::SameLine();
                
                std::string statusIcon = feature.enabled ? "🟢" : "🔴";
                ImGui::Text("%s %s", statusIcon.c_str(), feature.name.c_str());
                
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("%s", feature.description.c_str());
                }

                if (feature.enabled && !wasEnabled) {
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "[ACTIVATED]");
                } else if (!feature.enabled && wasEnabled) {
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "[DEACTIVATED]");
                }

                ImGui::TreePop();
            }
            
            ImGui::PopStyleVar();
        }
        ImGui::Spacing();
    }
}

void RobloxMenu::RenderCustomizationSection()
{
    ImGui::Text("Interface Customization");
    ImGui::Separator();
    ImGui::Text("Color Settings");
   
    if (ImGui::Checkbox("RGB Animation Mode", &m_rgbMode)) {
        if (m_rgbMode) {
            m_rgbTimer = 0.0f;
        }
    }
    
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Enable automatic color cycling animation");
    }

    if (!m_rgbMode) {
        ImGui::ColorEdit4("Base Theme Color", &m_baseColor.x, ImGuiColorEditFlags_NoAlpha);
    } else {
        ImGui::BeginDisabled();
        ImVec4 tempColor = m_baseColor;
        ImGui::ColorEdit4("Base Theme Color", &tempColor.x, ImGuiColorEditFlags_NoAlpha);
        ImGui::EndDisabled();
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "(RGB Mode Active)");
    }

    ImGui::Spacing();

    ImGui::Text("Appearance Settings");
    
    ImGui::SliderFloat("Menu Transparency", &m_menuAlpha, 0.3f, 1.0f, "%.2f");
    ImGui::SliderFloat("Corner Rounding", &m_roundingAmount, 0.0f, 20.0f, "%.1f px");

    ImGui::Spacing();

    if (m_isMobileDevice) {
        ImGui::Text("Mobile Settings");
        ImGui::SliderFloat("UI Scale Factor", &m_scaleFactor, 0.8f, 2.0f, "%.1f");
    }

    ImGui::Spacing();
    ImGui::Text("Theme Presets");
    
    if (ImGui::Button("Blue Theme")) {
        m_baseColor = ImVec4(0.2f, 0.4f, 0.8f, 1.0f);
        m_rgbMode = false;
    }
    ImGui::SameLine();
    
    if (ImGui::Button("Green Theme")) {
        m_baseColor = ImVec4(0.2f, 0.8f, 0.3f, 1.0f);
        m_rgbMode = false;
    }
    ImGui::SameLine();
    
    if (ImGui::Button("Purple Theme")) {
        m_baseColor = ImVec4(0.6f, 0.2f, 0.8f, 1.0f);
        m_rgbMode = false;
    }

    if (ImGui::Button("Orange Theme")) {
        m_baseColor = ImVec4(1.0f, 0.5f, 0.0f, 1.0f);
        m_rgbMode = false;
    }
    ImGui::SameLine();
    
    if (ImGui::Button("RGB Theme")) {
        m_rgbMode = true;
        m_rgbTimer = 0.0f;
    }
    ImGui::SameLine();
    
    if (ImGui::Button("Dark Theme")) {
        m_baseColor = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
        m_rgbMode = false;
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Text("Theme Preview");
    
    ImGui::PushStyleColor(ImGuiCol_Button, m_baseColor);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(m_baseColor.x + 0.1f, m_baseColor.y + 0.1f, m_baseColor.z + 0.1f, 1.0f));
    ImGui::Button("Sample Button");
    ImGui::PopStyleColor(2);
    
    ImGui::SameLine();
    ImGui::TextColored(m_baseColor, "Sample Colored Text");
}

void RobloxMenu::RenderPerformanceSection()
{
    if (!m_performanceMonitor) return;

    ImGui::Text("Performance Monitor");
    ImGui::Separator();

    float fps = m_performanceMonitor->GetFPS();
    float frameTime = m_performanceMonitor->GetFrameTime();
    float cpuUsage = m_performanceMonitor->GetCPUUsage();
    float memoryUsage = m_performanceMonitor->GetMemoryUsage();
    int ping = m_performanceMonitor->GetPing();

    ImGui::Text("Frame Rate:");
    ImGui::SameLine();
    if (fps >= 60.0f) {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%.1f FPS", fps);
    } else if (fps >= 30.0f) {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.1f FPS", fps);
    } else {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%.1f FPS", fps);
    }

    ImGui::Text("Frame Time: %.2f ms", frameTime);

    ImGui::Text("CPU Usage:");
    ImGui::ProgressBar(cpuUsage / 100.0f, ImVec2(-1, 0), std::to_string(static_cast<int>(cpuUsage)).append("%").c_str());

    ImGui::Text("Memory Usage:");
    ImGui::ProgressBar(memoryUsage / 100.0f, ImVec2(-1, 0), std::to_string(static_cast<int>(memoryUsage)).append("%").c_str());

    ImGui::Text("Ping: ");
    ImGui::SameLine();
    if (ping < 50) {
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%d ms", ping);
    } else if (ping < 100) {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%d ms", ping);
    } else {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "%d ms", ping);
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Text("Performance History");
    
    static std::vector<float> fpsHistory(100, 60.0f);
    fpsHistory.erase(fpsHistory.begin());
    fpsHistory.push_back(fps);
    
    ImGui::PlotLines("FPS Graph", fpsHistory.data(), static_cast<int>(fpsHistory.size()), 0, nullptr, 0.0f, 120.0f, ImVec2(0, 80));

    ImGui::Spacing();
    ImGui::Text("Performance Alerts:");
    
    if (fps < 30.0f) {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "• Low FPS detected! Consider optimization.");
    }
    
    if (cpuUsage > 80.0f) {
        ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "• High CPU usage detected!");
    }
    
    if (memoryUsage > 85.0f) {
        ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "• High memory usage detected!");
    }
    
    if (ping > 150) {
        ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "• High network latency detected!");
    }

    ImGui::Spacing();
    if (ImGui::Button("Quick Optimize", ImVec2(ImGui::GetContentRegionAvail().x, 30))) {
        if (m_optimizationManager) {
            m_optimizationManager->ApplyQuickOptimizations();
        }
    }
}

void RobloxMenu::RenderOptimizationSection()
{
    if (!m_optimizationManager) return;

    ImGui::Text("FPS Optimization Tools");
    ImGui::Separator();

    ImGui::Text("Quick Actions:");
    
    if (ImGui::Button("Clean Textures", ImVec2(150, 30))) {
        m_optimizationManager->CleanTextures();
    }
    ImGui::SameLine();
    
    if (ImGui::Button("Minimize Graphics", ImVec2(150, 30))) {
        m_optimizationManager->SetGraphicsToMinimum();
    }
    ImGui::SameLine();
    
    if (ImGui::Button("Reduce Effects", ImVec2(150, 30))) {
        m_optimizationManager->ReduceParticleEffects();
    }

    ImGui::Spacing();

    if (ImGui::Button("OPTIMIZE FPS NOW", ImVec2(ImGui::GetContentRegionAvail().x, 40))) {
        m_optimizationManager->ApplyAllOptimizations();
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Text("Advanced Options:");
    
    static bool autoOptimize = false;
    ImGui::Checkbox("Auto-optimize when FPS drops below 30", &autoOptimize);
    
    static int targetFPS = 60;
    ImGui::SliderInt("Target FPS", &targetFPS, 30, 120);
    
    static bool reduceLighting = true;
    ImGui::Checkbox("Reduce lighting quality", &reduceLighting);
    
    static bool disableShadows = true;
    ImGui::Checkbox("Disable shadows", &disableShadows);
    
    static bool reduceViewDistance = false;
    ImGui::Checkbox("Reduce view distance", &reduceViewDistance);

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::Text("Optimization Status:");
    
    bool texturesOptimized = m_optimizationManager->AreTexturesOptimized();
    bool graphicsMinimized = m_optimizationManager->AreGraphicsMinimized();
    bool effectsReduced = m_optimizationManager->AreEffectsReduced();

    ImGui::Text("Textures: %s", texturesOptimized ? "✅ Optimized" : "❌ Not Optimized");
    ImGui::Text("Graphics: %s", graphicsMinimized ? "✅ Minimized" : "❌ Standard");
    ImGui::Text("Effects: %s", effectsReduced ? "✅ Reduced" : "❌ Standard");

    ImGui::Spacing();

    if (ImGui::Button("🔄 Restore Default Settings", ImVec2(ImGui::GetContentRegionAvail().x, 30))) {
        m_optimizationManager->RestoreDefaults();
    }
}

void RobloxMenu::RenderAboutSection()
{
    ImGui::Text("About Roblox Enhanced Menu");
    ImGui::Separator();

    ImGui::TextWrapped("Roblox Enhanced Menu is a comprehensive modification interface designed to enhance your Roblox gaming experience. "
                      "Built with Dear ImGui for maximum performance and compatibility.");

    ImGui::Spacing();
    ImGui::Text("Technical Information:");
    ImGui::BulletText("Framework: Dear ImGui v1.89");
    ImGui::BulletText("Language: C++17");
    ImGui::BulletText("Platform: Cross-platform (Windows, Linux, macOS)");
    ImGui::BulletText("Mobile Support: Touch-optimized interface");

    ImGui::Spacing();
    ImGui::Text("System Requirements:");
    ImGui::BulletText("CPU: Any modern processor");
    ImGui::BulletText("RAM: 512MB available memory");
    ImGui::BulletText("Graphics: OpenGL 3.0+ compatible");
    ImGui::BulletText("OS: Windows 7+, Linux, macOS 10.12+");

    ImGui::Spacing();
    ImGui::Text("🔗 Links:");
    if (ImGui::Button("Documentation")) {
    }
    ImGui::SameLine();
    if (ImGui::Button("Report Bug")) {
    }
    ImGui::SameLine();
    if (ImGui::Button("Request Feature")) {
    }

    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "©");
}

void RobloxMenu::SetupStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();    
    ImVec4 accentColor = m_rgbMode ? m_baseColor : m_baseColor;
    
    style.WindowRounding = m_roundingAmount;
    style.ChildRounding = m_roundingAmount * 0.5f;
    style.FrameRounding = m_roundingAmount * 0.3f;
    style.GrabRounding = m_roundingAmount * 0.3f;
    style.TabRounding = m_roundingAmount * 0.3f;    
    style.WindowPadding = ImVec2(10 * m_scaleFactor, 10 * m_scaleFactor);
    style.FramePadding = ImVec2(8 * m_scaleFactor, 4 * m_scaleFactor);
    style.ItemSpacing = ImVec2(8 * m_scaleFactor, 6 * m_scaleFactor);
    style.ItemInnerSpacing = ImVec2(6 * m_scaleFactor, 4 * m_scaleFactor);
    
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, m_menuAlpha);
    colors[ImGuiCol_Header] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.3f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.4f);
    colors[ImGuiCol_HeaderActive] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.5f);
    colors[ImGuiCol_Button] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.4f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.6f);
    colors[ImGuiCol_ButtonActive] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.8f);
}

void RobloxMenu::HandleResponsiveDesign()
{
    ImGuiIO& io = ImGui::GetIO();
    
    if (m_isMobileDevice) {
        ImGuiStyle& style = ImGui::GetStyle();
        style.TouchExtraPadding = ImVec2(4.0f, 4.0f);
        
        if (m_windowSize.x > io.DisplaySize.x || m_windowSize.y > io.DisplaySize.y) {
            m_windowSize = ImVec2(io.DisplaySize.x * 0.95f, io.DisplaySize.y * 0.9f);
            m_windowPos = ImVec2(io.DisplaySize.x * 0.025f, io.DisplaySize.y * 0.05f);
        }
    }
}

void RobloxMenu::UpdateRGBAnimation()
{
    if (!m_rgbMode) return;
    
    float speed = 2.0f; // Cycle speed
    float r = (sinf(m_rgbTimer * speed) + 1.0f) * 0.5f;
    float g = (sinf(m_rgbTimer * speed + 2.0f) + 1.0f) * 0.5f;
    float b = (sinf(m_rgbTimer * speed + 4.0f) + 1.0f) * 0.5f;
    
    m_baseColor = ImVec4(r, g, b, 1.0f);
}

void RobloxMenu::SaveConfiguration()
{
    std::ofstream configFile("ttrick.txt");
    if (configFile.is_open()) {
        configFile << "rgb_mode=" << m_rgbMode << std::endl;
        configFile << "base_color_r=" << m_baseColor.x << std::endl;
        configFile << "base_color_g=" << m_baseColor.y << std::endl;
        configFile << "base_color_b=" << m_baseColor.z << std::endl;
        configFile << "menu_alpha=" << m_menuAlpha << std::endl;
        configFile << "rounding=" << m_roundingAmount << std::endl;
        configFile << "scale_factor=" << m_scaleFactor << std::endl;
        
        for (size_t i = 0; i < m_features.size(); ++i) {
            configFile << "feature_" << i << "=" << m_features[i].enabled << std::endl;
        }
        
        configFile.close();
        std::cout << "Configuration saved successfully!" << std::endl;
    }
}

void RobloxMenu::LoadConfiguration()
{
    std::ifstream configFile("ttrick.txt");
    if (configFile.is_open()) {
        std::string line;
        while (std::getline(configFile, line)) {
            size_t equalPos = line.find('=');
            if (equalPos != std::string::npos) {
                std::string key = line.substr(0, equalPos);
                std::string value = line.substr(equalPos + 1);
                
                if (key == "rgb_mode") {
                    m_rgbMode = (value == "1");
                } else if (key == "base_color_r") {
                    m_baseColor.x = std::stof(value);
                } else if (key == "base_color_g") {
                    m_baseColor.y = std::stof(value);
                } else if (key == "base_color_b") {
                    m_baseColor.z = std::stof(value);
                } else if (key == "menu_alpha") {
                    m_menuAlpha = std::stof(value);
                } else if (key == "rounding") {
                    m_roundingAmount = std::stof(value);
                } else if (key == "scale_factor") {
                    m_scaleFactor = std::stof(value);
                } else if (key.substr(0, 8) == "feature_") {
                    size_t featureIndex = std::stoul(key.substr(8));
                    if (featureIndex < m_features.size()) {
                        m_features[featureIndex].enabled = (value == "1");
                    }
                }
            }
        }
        configFile.close();
        std::cout << "Configuration loaded successfully!" << std::endl;
    }
}
