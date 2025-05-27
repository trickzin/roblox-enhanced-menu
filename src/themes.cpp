#include "themes.h"
#include <iostream>
#include <cmath>

ThemeManager::ThemeManager()
    : m_currentTheme(nullptr)
    , m_rgbAnimationTime(0.0f)
    , m_currentRGBColor(1.0f, 0.0f, 0.0f, 1.0f)
    , m_rgbSpeed(2.0f)
{
    InitializeThemes();
}

ThemeManager::~ThemeManager()
{
}

void ThemeManager::InitializeThemes()
{
    CreateDefaultThemes();
    
    if (!m_themes.empty()) {
        ApplyTheme("Dark Blue");
    }
    
    std::cout << "Theme Manager initialized with " << m_themes.size() << " themes." << std::endl;
}

void ThemeManager::CreateDefaultThemes()
{
    RegisterTheme(Theme(
        "Dark Blue",
        ImVec4(0.2f, 0.4f, 0.8f, 1.0f),    // Primary
        ImVec4(0.1f, 0.2f, 0.6f, 1.0f),    // Secondary
        ImVec4(0.3f, 0.6f, 1.0f, 1.0f),    // Accent
        ImVec4(0.06f, 0.06f, 0.06f, 1.0f), // Background
        ImVec4(1.0f, 1.0f, 1.0f, 1.0f),    // Text
        ImVec4(0.8f, 0.8f, 0.8f, 1.0f)     // Text Secondary
    ));

    RegisterTheme(Theme(
        "Green Matrix",
        ImVec4(0.0f, 0.8f, 0.2f, 1.0f),    // Primary
        ImVec4(0.0f, 0.6f, 0.1f, 1.0f),    // Secondary
        ImVec4(0.2f, 1.0f, 0.4f, 1.0f),    // Accent
        ImVec4(0.0f, 0.1f, 0.0f, 1.0f),    // Background
        ImVec4(0.2f, 1.0f, 0.2f, 1.0f),    // Text
        ImVec4(0.1f, 0.8f, 0.1f, 1.0f)     // Text Secondary
    ));

    RegisterTheme(Theme(
        "Purple Cosmic",
        ImVec4(0.6f, 0.2f, 0.8f, 1.0f),    // Primary
        ImVec4(0.4f, 0.1f, 0.6f, 1.0f),    // Secondary
        ImVec4(0.8f, 0.4f, 1.0f, 1.0f),    // Accent
        ImVec4(0.05f, 0.0f, 0.1f, 1.0f),   // Background
        ImVec4(1.0f, 0.9f, 1.0f, 1.0f),    // Text
        ImVec4(0.9f, 0.7f, 0.9f, 1.0f)     // Text Secondary
    ));

    RegisterTheme(Theme(
        "Orange Fire",
        ImVec4(1.0f, 0.5f, 0.0f, 1.0f),    // Primary
        ImVec4(0.8f, 0.3f, 0.0f, 1.0f),    // Secondary
        ImVec4(1.0f, 0.7f, 0.2f, 1.0f),    // Accent
        ImVec4(0.1f, 0.05f, 0.0f, 1.0f),   // Background
        ImVec4(1.0f, 0.95f, 0.9f, 1.0f),   // Text
        ImVec4(1.0f, 0.8f, 0.6f, 1.0f)     // Text Secondary
    ));

    RegisterTheme(Theme(
        "Ice Blue",
        ImVec4(0.0f, 0.7f, 1.0f, 1.0f),    // Primary
        ImVec4(0.0f, 0.5f, 0.8f, 1.0f),    // Secondary
        ImVec4(0.3f, 0.9f, 1.0f, 1.0f),    // Accent
        ImVec4(0.0f, 0.05f, 0.1f, 1.0f),   // Background
        ImVec4(0.9f, 0.95f, 1.0f, 1.0f),   // Text
        ImVec4(0.7f, 0.85f, 1.0f, 1.0f)    // Text Secondary
    ));

    RegisterTheme(Theme(
        "RGB Rainbow",
        ImVec4(1.0f, 0.0f, 0.0f, 1.0f),    // Primary (will be animated)
        ImVec4(0.5f, 0.0f, 0.5f, 1.0f),    // Secondary
        ImVec4(1.0f, 1.0f, 1.0f, 1.0f),    // Accent
        ImVec4(0.05f, 0.05f, 0.05f, 1.0f), // Background
        ImVec4(1.0f, 1.0f, 1.0f, 1.0f),    // Text
        ImVec4(0.9f, 0.9f, 0.9f, 1.0f),    // Text Secondary
        true                                 // RGB support
    ));

    RegisterTheme(Theme(
        "Dark Minimalist",
        ImVec4(0.3f, 0.3f, 0.3f, 1.0f),    // Primary
        ImVec4(0.2f, 0.2f, 0.2f, 1.0f),    // Secondary
        ImVec4(0.5f, 0.5f, 0.5f, 1.0f),    // Accent
        ImVec4(0.08f, 0.08f, 0.08f, 1.0f), // Background
        ImVec4(0.95f, 0.95f, 0.95f, 1.0f), // Text
        ImVec4(0.7f, 0.7f, 0.7f, 1.0f)     // Text Secondary
    ));

    RegisterTheme(Theme(
        "Roblox Classic",
        ImVec4(0.0f, 0.6f, 1.0f, 1.0f),    // Primary (Roblox Blue)
        ImVec4(0.0f, 0.4f, 0.8f, 1.0f),    // Secondary
        ImVec4(0.2f, 0.8f, 1.0f, 1.0f),    // Accent
        ImVec4(0.02f, 0.02f, 0.08f, 1.0f), // Background
        ImVec4(1.0f, 1.0f, 1.0f, 1.0f),    // Text
        ImVec4(0.9f, 0.9f, 0.9f, 1.0f)     // Text Secondary
    ));
}

void ThemeManager::RegisterTheme(const Theme& theme)
{
    m_themes[theme.name] = theme;
    m_themeNames.push_back(theme.name);
}

void ThemeManager::ApplyTheme(const std::string& themeName)
{
    auto it = m_themes.find(themeName);
    if (it != m_themes.end()) {
        m_currentTheme = &it->second;
        ApplyImGuiStyle(*m_currentTheme);
        std::cout << "Applied theme: " << themeName << std::endl;
    } else {
        std::cout << "Theme not found: " << themeName << std::endl;
    }
}

void ThemeManager::ApplyCustomTheme(const Theme& theme)
{
    static Theme customTheme = theme;
    m_currentTheme = &customTheme;
    ApplyImGuiStyle(*m_currentTheme);
    
    std::cout << "Applied custom theme: " << theme.name << std::endl;
}

const Theme* ThemeManager::GetTheme(const std::string& name) const
{
    auto it = m_themes.find(name);
    return (it != m_themes.end()) ? &it->second : nullptr;
}

void ThemeManager::ApplyImGuiStyle(const Theme& theme, float alpha, float rounding)
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    style.WindowRounding = rounding;
    style.ChildRounding = rounding * 0.5f;
    style.FrameRounding = rounding * 0.3f;
    style.GrabRounding = rounding * 0.3f;
    style.TabRounding = rounding * 0.3f;
    style.ScrollbarRounding = rounding * 0.5f;

    ImVec4 primaryColor = theme.primaryColor;
    ImVec4 secondaryColor = theme.secondaryColor;
    ImVec4 accentColor = theme.accentColor;
    
    if (theme.supportRGB) {
        primaryColor = m_currentRGBColor;
    }

    colors[ImGuiCol_WindowBg] = ImVec4(theme.backgroundColor.x, theme.backgroundColor.y, theme.backgroundColor.z, alpha);
    colors[ImGuiCol_ChildBg] = ImVec4(theme.backgroundColor.x + 0.02f, theme.backgroundColor.y + 0.02f, theme.backgroundColor.z + 0.02f, alpha);
    colors[ImGuiCol_PopupBg] = ImVec4(theme.backgroundColor.x + 0.05f, theme.backgroundColor.y + 0.05f, theme.backgroundColor.z + 0.05f, alpha);

    colors[ImGuiCol_FrameBg] = ImVec4(secondaryColor.x, secondaryColor.y, secondaryColor.z, 0.5f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.4f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.6f);

    colors[ImGuiCol_TitleBg] = ImVec4(secondaryColor.x, secondaryColor.y, secondaryColor.z, 0.8f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.8f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(secondaryColor.x, secondaryColor.y, secondaryColor.z, 0.5f);

    colors[ImGuiCol_MenuBarBg] = ImVec4(theme.backgroundColor.x + 0.05f, theme.backgroundColor.y + 0.05f, theme.backgroundColor.z + 0.05f, alpha);

    colors[ImGuiCol_Button] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.6f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.8f);
    colors[ImGuiCol_ButtonActive] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 1.0f);

    colors[ImGuiCol_Header] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.3f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.4f);
    colors[ImGuiCol_HeaderActive] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.5f);

    colors[ImGuiCol_Separator] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.5f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.8f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 1.0f);

    colors[ImGuiCol_ResizeGrip] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.3f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.6f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.9f);

    colors[ImGuiCol_Tab] = ImVec4(secondaryColor.x, secondaryColor.y, secondaryColor.z, 0.8f);
    colors[ImGuiCol_TabHovered] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.8f);
    colors[ImGuiCol_TabActive] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 1.0f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(secondaryColor.x, secondaryColor.y, secondaryColor.z, 0.6f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.7f);

    colors[ImGuiCol_Text] = theme.textColor;
    colors[ImGuiCol_TextDisabled] = theme.textColorSecondary;
    colors[ImGuiCol_CheckMark] = accentColor;

    colors[ImGuiCol_SliderGrab] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.8f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 1.0f);

    colors[ImGuiCol_ScrollbarBg] = ImVec4(theme.backgroundColor.x + 0.02f, theme.backgroundColor.y + 0.02f, theme.backgroundColor.z + 0.02f, 0.5f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.5f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.7f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.9f);

    colors[ImGuiCol_TableHeaderBg] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.3f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.5f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(primaryColor.x, primaryColor.y, primaryColor.z, 0.2f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.06f);
}

ImVec4 ThemeManager::CreateRGBColor(float time, float speed)
{
    float r = (sinf(time * speed) + 1.0f) * 0.5f;
    float g = (sinf(time * speed + 2.094f) + 1.0f) * 0.5f; // 2π/3 offset
    float b = (sinf(time * speed + 4.188f) + 1.0f) * 0.5f; // 4π/3 offset
    
    return ImVec4(r, g, b, 1.0f);
}

ImVec4 ThemeManager::BlendColors(const ImVec4& color1, const ImVec4& color2, float factor)
{
    factor = std::max(0.0f, std::min(1.0f, factor));
    
    return ImVec4(
        color1.x + (color2.x - color1.x) * factor,
        color1.y + (color2.y - color1.y) * factor,
        color1.z + (color2.z - color1.z) * factor,
        color1.w + (color2.w - color1.w) * factor
    );
}

ImVec4 ThemeManager::AdjustBrightness(const ImVec4& color, float factor)
{
    return ImVec4(
        std::max(0.0f, std::min(1.0f, color.x * factor)),
        std::max(0.0f, std::min(1.0f, color.y * factor)),
        std::max(0.0f, std::min(1.0f, color.z * factor)),
        color.w
    );
}

void ThemeManager::UpdateRGBAnimation(float deltaTime)
{
    m_rgbAnimationTime += deltaTime;
    m_currentRGBColor = CreateRGBColor(m_rgbAnimationTime, m_rgbSpeed);
    
    if (m_currentTheme && m_currentTheme->supportRGB) {
        ApplyImGuiStyle(*m_currentTheme);
    }
}
