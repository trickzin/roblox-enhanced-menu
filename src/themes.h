#ifndef THEMES_H
#define THEMES_H

#include "imgui.h"
#include <string>
#include <map>
#include <vector>

struct Theme {
    std::string name;
    ImVec4 primaryColor;
    ImVec4 secondaryColor;
    ImVec4 accentColor;
    ImVec4 backgroundColor;
    ImVec4 textColor;
    ImVec4 textColorSecondary;
    bool supportRGB;
    
    Theme(const std::string& n, ImVec4 primary, ImVec4 secondary, ImVec4 accent, 
          ImVec4 background, ImVec4 text, ImVec4 textSec, bool rgb = false)
        : name(n), primaryColor(primary), secondaryColor(secondary), accentColor(accent)
        , backgroundColor(background), textColor(text), textColorSecondary(textSec)
        , supportRGB(rgb) {}
};

class ThemeManager {
public:
    ThemeManager();
    ~ThemeManager();

    void InitializeThemes();
    void ApplyTheme(const std::string& themeName);
    void ApplyCustomTheme(const Theme& theme);
    
    ImVec4 CreateRGBColor(float time, float speed = 2.0f);
    ImVec4 BlendColors(const ImVec4& color1, const ImVec4& color2, float factor);
    ImVec4 AdjustBrightness(const ImVec4& color, float factor);
    
    const std::vector<std::string>& GetThemeNames() const { return m_themeNames; }
    const Theme* GetCurrentTheme() const { return m_currentTheme; }
    const Theme* GetTheme(const std::string& name) const;
    
    void ApplyImGuiStyle(const Theme& theme, float alpha = 1.0f, float rounding = 8.0f);
    
    void UpdateRGBAnimation(float deltaTime);
    ImVec4 GetAnimatedRGBColor() const { return m_currentRGBColor; }

private:
    void CreateDefaultThemes();
    void RegisterTheme(const Theme& theme);
    
    std::map<std::string, Theme> m_themes;
    std::vector<std::string> m_themeNames;
    const Theme* m_currentTheme;
    
    float m_rgbAnimationTime;
    ImVec4 m_currentRGBColor;
    float m_rgbSpeed;
};

#endif
