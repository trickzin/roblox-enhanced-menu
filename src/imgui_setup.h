#ifndef IMGUI_SETUP_H
#define IMGUI_SETUP_H

#include "imgui.h"

namespace ImGuiSetup {
    void SetupStyle();
    void SetupColors();
    void SetupFonts();    
    void LoadFonts();
    void LoadDefaultFont();
    void LoadIconFont();    
    void ConfigureIO();
    void SetupDocking();    
    void SetupForMobile();
    void SetupForDesktop();
}

#endif
