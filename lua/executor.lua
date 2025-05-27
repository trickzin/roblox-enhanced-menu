-- Criado por: trickzqw
-- Email: sintofaltadela@gmail.com(não existe)

local RobloxMenu = loadstring(game:HttpGet("https://raw.githubusercontent.com/trickzqw/roblox-enhanced-menu/main/lua/menu.lua"))()

local menu = RobloxMenu.new()
menu:Initialize()

game.StarterGui:SetCore("SendNotification", {
    Title = "Roblox Enhanced Menu";
    Text = "Menu carregado! Pressione INSERT para abrir";
    Duration = 5;
})