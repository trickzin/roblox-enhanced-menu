-- Exemplo de uso rápido
-- Criado por: trickzqw

loadstring(game:HttpGet("https://raw.githubusercontent.com/trickzqw/roblox-enhanced-menu/main/lua/executor.lua"))()

-- OU carregamento manual:
--[[
local RobloxMenu = loadstring(game:HttpGet("https://raw.githubusercontent.com/trickzqw/roblox-enhanced-menu/main/lua/menu.lua"))()
local menu = RobloxMenu.new()
menu:Initialize()
--]]

print("Menu carregado! Pressione INSERT para abrir/fechar")