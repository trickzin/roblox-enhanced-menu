-- Criado por: trickzqw
-- Email: sintofaltadela@gmail.com

local RobloxMenu = {}
RobloxMenu.__index = RobloxMenu
local Players = game:GetService("Players")
local RunService = game:GetService("RunService")
local UserInputService = game:GetService("UserInputService")
local TweenService = game:GetService("TweenService")
local CoreGui = game:GetService("CoreGui")

local LocalPlayer = Players.LocalPlayer
local Mouse = LocalPlayer:GetMouse()
local Camera = workspace.CurrentCamera

function RobloxMenu.new()
    local self = setmetatable({}, RobloxMenu)
    
    self.features = {
        esp = {
            playerESP = false,
            itemESP = false,
            distanceESP = false
        },
        movement = {
            speedBoost = false,
            jumpBoost = false,
            noClip = false,
            flyMode = false,
            speedValue = 50,
            jumpValue = 100
        },
        combat = {
            aimbot = false,
            autoAttack = false,
            damageBoost = false,
            aimbotFOV = 100
        },
        utility = {
            autoFarm = false,
            teleport = false,
            godMode = false
        }
    }
    
    self.theme = {
        currentTheme = "Dark Blue",
        rgbMode = false,
        colors = {
            primary = Color3.fromRGB(51, 102, 204),
            secondary = Color3.fromRGB(25, 51, 153),
            accent = Color3.fromRGB(76, 153, 255),
            background = Color3.fromRGB(15, 15, 15),
            text = Color3.fromRGB(255, 255, 255)
        }
    }
    
    self.connections = {}
    self.espObjects = {}
    
    return self
end

function RobloxMenu:CreateGUI()
    local screenGui = Instance.new("ScreenGui")
    screenGui.Name = "RobloxEnhancedMenu"
    screenGui.ResetOnSpawn = false
    screenGui.ZIndexBehavior = Enum.ZIndexBehavior.Sibling
    
    if CoreGui:FindFirstChild("RobloxEnhancedMenu") then
        CoreGui:FindFirstChild("RobloxEnhancedMenu"):Destroy()
    end
    
    screenGui.Parent = CoreGui
    
    local mainFrame = Instance.new("Frame")
    mainFrame.Name = "MainFrame"
    mainFrame.Size = UDim2.new(0, 600, 0, 400)
    mainFrame.Position = UDim2.new(0.5, -300, 0.5, -200)
    mainFrame.BackgroundColor3 = self.theme.colors.background
    mainFrame.BorderSizePixel = 0
    mainFrame.Active = true
    mainFrame.Draggable = true
    mainFrame.Parent = screenGui
    
    local corner = Instance.new("UICorner")
    corner.CornerRadius = UDim.new(0, 12)
    corner.Parent = mainFrame
    
    local header = Instance.new("Frame")
    header.Name = "Header"
    header.Size = UDim2.new(1, 0, 0, 50)
    header.Position = UDim2.new(0, 0, 0, 0)
    header.BackgroundColor3 = self.theme.colors.primary
    header.BorderSizePixel = 0
    header.Parent = mainFrame
    
    local headerCorner = Instance.new("UICorner")
    headerCorner.CornerRadius = UDim.new(0, 12)
    headerCorner.Parent = header
    
    local title = Instance.new("TextLabel")
    title.Name = "Title"
    title.Size = UDim2.new(1, -100, 1, 0)
    title.Position = UDim2.new(0, 10, 0, 0)
    title.BackgroundTransparency = 1
    title.Text = "🎮 ROBLOX ENHANCED MENU v1.0"
    title.TextColor3 = self.theme.colors.text
    title.TextScaled = true
    title.Font = Enum.Font.GothamBold
    title.Parent = header
    
    local closeButton = Instance.new("TextButton")
    closeButton.Name = "CloseButton"
    closeButton.Size = UDim2.new(0, 40, 0, 40)
    closeButton.Position = UDim2.new(1, -45, 0, 5)
    closeButton.BackgroundColor3 = Color3.fromRGB(255, 50, 50)
    closeButton.BorderSizePixel = 0
    closeButton.Text = "✕"
    closeButton.TextColor3 = Color3.fromRGB(255, 255, 255)
    closeButton.TextScaled = true
    closeButton.Font = Enum.Font.GothamBold
    closeButton.Parent = header
    
    local closeCorner = Instance.new("UICorner")
    closeCorner.CornerRadius = UDim.new(0, 8)
    closeCorner.Parent = closeButton
    
    closeButton.MouseButton1Click:Connect(function()
        self:Toggle()
    end)
    
    local tabContainer = Instance.new("Frame")
    tabContainer.Name = "TabContainer"
    tabContainer.Size = UDim2.new(1, -20, 1, -70)
    tabContainer.Position = UDim2.new(0, 10, 0, 60)
    tabContainer.BackgroundTransparency = 1
    tabContainer.Parent = mainFrame
    
    self:CreateTabs(tabContainer)
    
    self.gui = screenGui
    self.mainFrame = mainFrame
    
    return screenGui
end

function RobloxMenu:CreateTabs(parent)
    local tabButtons = Instance.new("Frame")
    tabButtons.Name = "TabButtons"
    tabButtons.Size = UDim2.new(1, 0, 0, 40)
    tabButtons.Position = UDim2.new(0, 0, 0, 0)
    tabButtons.BackgroundTransparency = 1
    tabButtons.Parent = parent
    
    local tabButtonsLayout = Instance.new("UIListLayout")
    tabButtonsLayout.FillDirection = Enum.FillDirection.Horizontal
    tabButtonsLayout.HorizontalAlignment = Enum.HorizontalAlignment.Left
    tabButtonsLayout.SortOrder = Enum.SortOrder.LayoutOrder
    tabButtonsLayout.Padding = UDim.new(0, 5)
    tabButtonsLayout.Parent = tabButtons
    
    local tabContent = Instance.new("Frame")
    tabContent.Name = "TabContent"
    tabContent.Size = UDim2.new(1, 0, 1, -50)
    tabContent.Position = UDim2.new(0, 0, 0, 50)
    tabContent.BackgroundTransparency = 1
    tabContent.Parent = parent
    
    local tabs = {
        {name = "Créditos", content = "credits"},
        {name = "Funcionalidades", content = "features"},
        {name = "Performance", content = "performance"},
        {name = "Personalização", content = "customization"}
    }
    
    for i, tab in ipairs(tabs) do
        local button = Instance.new("TextButton")
        button.Name = "TabButton" .. i
        button.Size = UDim2.new(0, 140, 1, 0)
        button.BackgroundColor3 = self.theme.colors.secondary
        button.BorderSizePixel = 0
        button.Text = tab.name
        button.TextColor3 = self.theme.colors.text
        button.TextScaled = true
        button.Font = Enum.Font.Gotham
        button.LayoutOrder = i
        button.Parent = tabButtons
        
        local buttonCorner = Instance.new("UICorner")
        buttonCorner.CornerRadius = UDim.new(0, 6)
        buttonCorner.Parent = button
        
        local content = self:CreateTabContent(tab.content, tabContent)
        content.Visible = (i == 1)
        
        button.MouseButton1Click:Connect(function()
            for _, child in pairs(tabContent:GetChildren()) do
                if child:IsA("Frame") then
                    child.Visible = false
                end
            end
            
            content.Visible = true
            
            for _, btn in pairs(tabButtons:GetChildren()) do
                if btn:IsA("TextButton") then
                    btn.BackgroundColor3 = self.theme.colors.secondary
                end
            end
            button.BackgroundColor3 = self.theme.colors.primary
        end)
        
        if i == 1 then
            button.BackgroundColor3 = self.theme.colors.primary
        end
    end
end

function RobloxMenu:CreateTabContent(contentType, parent)
    local content = Instance.new("Frame")
    content.Name = contentType
    content.Size = UDim2.new(1, 0, 1, 0)
    content.BackgroundTransparency = 1
    content.Parent = parent
    
    if contentType == "credits" then
        self:CreateCreditsTab(content)
    elseif contentType == "features" then
        self:CreateFeaturesTab(content)
    elseif contentType == "performance" then
        self:CreatePerformanceTab(content)
    elseif contentType == "customization" then
        self:CreateCustomizationTab(content)
    end
    
    return content
end

function RobloxMenu:CreateCreditsTab(parent)
    local scrollFrame = Instance.new("ScrollingFrame")
    scrollFrame.Size = UDim2.new(1, 0, 1, 0)
    scrollFrame.BackgroundTransparency = 1
    scrollFrame.BorderSizePixel = 0
    scrollFrame.ScrollBarThickness = 6
    scrollFrame.Parent = parent
    
    local layout = Instance.new("UIListLayout")
    layout.Padding = UDim.new(0, 10)
    layout.SortOrder = Enum.SortOrder.LayoutOrder
    layout.Parent = scrollFrame
    
    local titleLabel = Instance.new("TextLabel")
    titleLabel.Size = UDim2.new(1, 0, 0, 50)
    titleLabel.BackgroundTransparency = 1
    titleLabel.Text = "ROBLOX ENHANCED MENU"
    titleLabel.TextColor3 = self.theme.colors.accent
    titleLabel.TextScaled = true
    titleLabel.Font = Enum.Font.GothamBold
    titleLabel.LayoutOrder = 1
    titleLabel.Parent = scrollFrame
    
    local creatorInfo = {
        "Criado por: trickzqw",
        "Contato: sintofaltadela@gmail.com",
        "Website: https://trickzin.github.io/trick-little-man/",
        "Versão: 0.0.1 - Data: 2025"
    }
    
    for i, info in ipairs(creatorInfo) do
        local label = Instance.new("TextLabel")
        label.Size = UDim2.new(1, 0, 0, 30)
        label.BackgroundTransparency = 1
        label.Text = info
        label.TextColor3 = self.theme.colors.text
        label.TextScaled = true
        label.Font = Enum.Font.Gotham
        label.TextXAlignment = Enum.TextXAlignment.Left
        label.LayoutOrder = i + 1
        label.Parent = scrollFrame
    end
    
    scrollFrame.CanvasSize = UDim2.new(0, 0, 0, layout.AbsoluteContentSize.Y)
end

function RobloxMenu:CreateFeaturesTab(parent)
    local scrollFrame = Instance.new("ScrollingFrame")
    scrollFrame.Size = UDim2.new(1, 0, 1, 0)
    scrollFrame.BackgroundTransparency = 1
    scrollFrame.BorderSizePixel = 0
    scrollFrame.ScrollBarThickness = 6
    scrollFrame.Parent = parent
    
    local layout = Instance.new("UIListLayout")
    layout.Padding = UDim.new(0, 15)
    layout.SortOrder = Enum.SortOrder.LayoutOrder
    layout.Parent = scrollFrame
    
    local categories = {
        {name = "🔍 ESP Features", features = {"playerESP", "itemESP", "distanceESP"}, group = "esp"},
        {name = "🏃 Movement Features", features = {"speedBoost", "jumpBoost", "noClip", "flyMode"}, group = "movement"},
        {name = "⚔️ Combat Features", features = {"aimbot", "autoAttack", "damageBoost"}, group = "combat"},
        {name = "🛠️ Utility Features", features = {"autoFarm", "teleport", "godMode"}, group = "utility"}
    }
    
    for categoryIndex, category in ipairs(categories) do
        local categoryTitle = Instance.new("TextLabel")
        categoryTitle.Size = UDim2.new(1, 0, 0, 30)
        categoryTitle.BackgroundTransparency = 1
        categoryTitle.Text = category.name
        categoryTitle.TextColor3 = self.theme.colors.accent
        categoryTitle.TextScaled = true
        categoryTitle.Font = Enum.Font.GothamBold
        categoryTitle.TextXAlignment = Enum.TextXAlignment.Left
        categoryTitle.LayoutOrder = categoryIndex * 10
        categoryTitle.Parent = scrollFrame
        
        local featuresContainer = Instance.new("Frame")
        featuresContainer.Size = UDim2.new(1, 0, 0, #category.features * 40)
        featuresContainer.BackgroundColor3 = Color3.fromRGB(25, 25, 25)
        featuresContainer.BorderSizePixel = 0
        featuresContainer.LayoutOrder = categoryIndex * 10 + 1
        featuresContainer.Parent = scrollFrame
        
        local containerCorner = Instance.new("UICorner")
        containerCorner.CornerRadius = UDim.new(0, 8)
        containerCorner.Parent = featuresContainer
        
        local featuresLayout = Instance.new("UIListLayout")
        featuresLayout.Padding = UDim.new(0, 5)
        featuresLayout.SortOrder = Enum.SortOrder.LayoutOrder
        featuresLayout.Parent = featuresContainer
        
        for i, featureName in ipairs(category.features) do
            self:CreateFeatureToggle(featuresContainer, featureName, category.group, i)
        end
    end
    
    scrollFrame.CanvasSize = UDim2.new(0, 0, 0, layout.AbsoluteContentSize.Y)
end

function RobloxMenu:CreateFeatureToggle(parent, featureName, group, order)
    local featureFrame = Instance.new("Frame")
    featureFrame.Size = UDim2.new(1, -10, 0, 35)
    featureFrame.Position = UDim2.new(0, 5, 0, 0)
    featureFrame.BackgroundTransparency = 1
    featureFrame.LayoutOrder = order
    featureFrame.Parent = parent
    
    local nameLabel = Instance.new("TextLabel")
    nameLabel.Size = UDim2.new(0.7, 0, 1, 0)
    nameLabel.Position = UDim2.new(0, 0, 0, 0)
    nameLabel.BackgroundTransparency = 1
    nameLabel.Text = self:GetFeatureDisplayName(featureName)
    nameLabel.TextColor3 = self.theme.colors.text
    nameLabel.TextScaled = true
    nameLabel.Font = Enum.Font.Gotham
    nameLabel.TextXAlignment = Enum.TextXAlignment.Left
    nameLabel.Parent = featureFrame
    
    local toggleButton = Instance.new("TextButton")
    toggleButton.Size = UDim2.new(0, 60, 0, 25)
    toggleButton.Position = UDim2.new(1, -70, 0.5, -12.5)
    toggleButton.BackgroundColor3 = Color3.fromRGB(255, 50, 50)
    toggleButton.BorderSizePixel = 0
    toggleButton.Text = "OFF"
    toggleButton.TextColor3 = Color3.fromRGB(255, 255, 255)
    toggleButton.TextScaled = true
    toggleButton.Font = Enum.Font.GothamBold
    toggleButton.Parent = featureFrame
    
    local toggleCorner = Instance.new("UICorner")
    toggleCorner.CornerRadius = UDim.new(0, 12)
    toggleCorner.Parent = toggleButton
    
    toggleButton.MouseButton1Click:Connect(function()
        self.features[group][featureName] = not self.features[group][featureName]
        
        if self.features[group][featureName] then
            toggleButton.BackgroundColor3 = Color3.fromRGB(50, 255, 50)
            toggleButton.Text = "ON"
            self:EnableFeature(featureName, group)
        else
            toggleButton.BackgroundColor3 = Color3.fromRGB(255, 50, 50)
            toggleButton.Text = "OFF"
            self:DisableFeature(featureName, group)
        end
    end)
end

function RobloxMenu:GetFeatureDisplayName(featureName)
    local displayNames = {
        playerESP = "Player ESP",
        itemESP = "Item ESP", 
        distanceESP = "Distance ESP",
        speedBoost = "Speed Boost",
        jumpBoost = "Jump Boost",
        noClip = "No Clip",
        flyMode = "Fly Mode",
        aimbot = "Aimbot",
        autoAttack = "Auto Attack",
        damageBoost = "Damage Boost",
        autoFarm = "Auto Farm",
        teleport = "Teleport",
        godMode = "God Mode"
    }
    return displayNames[featureName] or featureName
end

function RobloxMenu:EnableFeature(featureName, group)
    if group == "movement" then
        if featureName == "speedBoost" then
            self:EnableSpeedBoost()
        elseif featureName == "jumpBoost" then
            self:EnableJumpBoost()
        elseif featureName == "flyMode" then
            self:EnableFlyMode()
        end
    elseif group == "esp" then
        if featureName == "playerESP" then
            self:EnablePlayerESP()
        end
    elseif group == "utility" then
        if featureName == "godMode" then
            self:EnableGodMode()
        end
    end
end

function RobloxMenu:DisableFeature(featureName, group)
    if group == "movement" then
        if featureName == "speedBoost" then
            self:DisableSpeedBoost()
        elseif featureName == "jumpBoost" then
            self:DisableJumpBoost()
        elseif featureName == "flyMode" then
            self:DisableFlyMode()
        end
    elseif group == "esp" then
        if featureName == "playerESP" then
            self:DisablePlayerESP()
        end
    elseif group == "utility" then
        if featureName == "godMode" then
            self:DisableGodMode()
        end
    end
end

function RobloxMenu:EnableSpeedBoost()
    if LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("Humanoid") then
        LocalPlayer.Character.Humanoid.WalkSpeed = self.features.movement.speedValue
    end
end

function RobloxMenu:DisableSpeedBoost()
    if LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("Humanoid") then
        LocalPlayer.Character.Humanoid.WalkSpeed = 16
    end
end

function RobloxMenu:EnableJumpBoost()
    if LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("Humanoid") then
        LocalPlayer.Character.Humanoid.JumpPower = self.features.movement.jumpValue
    end
end

function RobloxMenu:DisableJumpBoost()
    if LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("Humanoid") then
        LocalPlayer.Character.Humanoid.JumpPower = 50
    end
end

function RobloxMenu:EnablePlayerESP()
    for _, player in pairs(Players:GetPlayers()) do
        if player ~= LocalPlayer then
            self:CreateESPForPlayer(player)
        end
    end
    
    self.connections["playerESP"] = Players.PlayerAdded:Connect(function(player)
        self:CreateESPForPlayer(player)
    end)
end

function RobloxMenu:DisablePlayerESP()
    if self.connections["playerESP"] then
        self.connections["playerESP"]:Disconnect()
        self.connections["playerESP"] = nil
    end
    
    for _, espObject in pairs(self.espObjects) do
        if espObject then
            espObject:Destroy()
        end
    end
    self.espObjects = {}
end

function RobloxMenu:CreateESPForPlayer(player)
    local function createESP()
        if player.Character and player.Character:FindFirstChild("HumanoidRootPart") then
            local highlight = Instance.new("Highlight")
            highlight.Parent = player.Character
            highlight.FillColor = Color3.fromRGB(255, 0, 0)
            highlight.OutlineColor = Color3.fromRGB(255, 255, 255)
            highlight.FillTransparency = 0.5
            highlight.OutlineTransparency = 0
            
            table.insert(self.espObjects, highlight)
        end
    end
    
    if player.Character then
        createESP()
    end
    
    player.CharacterAdded:Connect(createESP)
end

function RobloxMenu:EnableGodMode()
    if LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("Humanoid") then
        LocalPlayer.Character.Humanoid.MaxHealth = math.huge
        LocalPlayer.Character.Humanoid.Health = math.huge
    end
end

function RobloxMenu:DisableGodMode()
    if LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("Humanoid") then
        LocalPlayer.Character.Humanoid.MaxHealth = 100
        LocalPlayer.Character.Humanoid.Health = 100
    end
end

function RobloxMenu:EnableFlyMode()
    local bodyVelocity = Instance.new("BodyVelocity")
    local bodyAngularVelocity = Instance.new("BodyAngularVelocity")
    
    if LocalPlayer.Character and LocalPlayer.Character:FindFirstChild("HumanoidRootPart") then
        bodyVelocity.Parent = LocalPlayer.Character.HumanoidRootPart
        bodyAngularVelocity.Parent = LocalPlayer.Character.HumanoidRootPart
        
        bodyVelocity.MaxForce = Vector3.new(math.huge, math.huge, math.huge)
        bodyVelocity.Velocity = Vector3.new(0, 0, 0)
        
        bodyAngularVelocity.MaxTorque = Vector3.new(math.huge, math.huge, math.huge)
        bodyAngularVelocity.AngularVelocity = Vector3.new(0, 0, 0)
        
        self.flyBodyVelocity = bodyVelocity
        self.flyBodyAngularVelocity = bodyAngularVelocity
        
        self.connections["flyMode"] = RunService.Heartbeat:Connect(function()
            if UserInputService:IsKeyDown(Enum.KeyCode.W) then
                bodyVelocity.Velocity = Camera.CFrame.LookVector * 50
            elseif UserInputService:IsKeyDown(Enum.KeyCode.S) then
                bodyVelocity.Velocity = Camera.CFrame.LookVector * -50
            elseif UserInputService:IsKeyDown(Enum.KeyCode.A) then
                bodyVelocity.Velocity = Camera.CFrame.RightVector * -50
            elseif UserInputService:IsKeyDown(Enum.KeyCode.D) then
                bodyVelocity.Velocity = Camera.CFrame.RightVector * 50
            elseif UserInputService:IsKeyDown(Enum.KeyCode.Space) then
                bodyVelocity.Velocity = Vector3.new(0, 50, 0)
            elseif UserInputService:IsKeyDown(Enum.KeyCode.LeftShift) then
                bodyVelocity.Velocity = Vector3.new(0, -50, 0)
            else
                bodyVelocity.Velocity = Vector3.new(0, 0, 0)
            end
        end)
    end
end

function RobloxMenu:DisableFlyMode()
    if self.connections["flyMode"] then
        self.connections["flyMode"]:Disconnect()
        self.connections["flyMode"] = nil
    end
    
    if self.flyBodyVelocity then
        self.flyBodyVelocity:Destroy()
        self.flyBodyVelocity = nil
    end
    
    if self.flyBodyAngularVelocity then
        self.flyBodyAngularVelocity:Destroy()
        self.flyBodyAngularVelocity = nil
    end
end

function RobloxMenu:CreatePerformanceTab(parent)
    local label = Instance.new("TextLabel")
    label.Size = UDim2.new(1, 0, 1, 0)
    label.BackgroundTransparency = 1
    label.Text = "📊 Performance Monitor\n\nFPS: 60\nPing: 50ms\nMemory: 45%"
    label.TextColor3 = self.theme.colors.text
    label.TextScaled = true
    label.Font = Enum.Font.Gotham
    label.Parent = parent
end

function RobloxMenu:CreateCustomizationTab(parent)
    local label = Instance.new("TextLabel")
    label.Size = UDim2.new(1, 0, 1, 0)
    label.BackgroundTransparency = 1
    label.Text = "🎨 Customization\n\nTemas Disponíveis\nModo RGB\nPersonalizar Cores"
    label.TextColor3 = self.theme.colors.text
    label.TextScaled = true
    label.Font = Enum.Font.Gotham
    label.Parent = parent
end

function RobloxMenu:Toggle()
    if self.gui then
        self.gui.Enabled = not self.gui.Enabled
    end
end

function RobloxMenu:Initialize()
    self:CreateGUI()
    
    UserInputService.InputBegan:Connect(function(input, gameProcessed)
        if not gameProcessed and input.KeyCode == Enum.KeyCode.Insert then
            self:Toggle()
        end
    end)
    
    print("Menu carregado!")
    print("Pressione INSERT para abrir/fechar o menu")
end

return RobloxMenu