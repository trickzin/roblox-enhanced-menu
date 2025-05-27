local config = {
    AttackDistance = 20,
    FlyHeight = 15,
    AttackDelay = 0.5,
    DebugMode = false
}

local Players = game:GetService("Players")
local Workspace = game:GetService("Workspace")
local LocalPlayer = Players.LocalPlayer
local Character = LocalPlayer.Character or LocalPlayer.CharacterAdded:Wait()
local Humanoid = Character:WaitForChild("Humanoid")
local HumanoidRootPart = Character:WaitForChild("HumanoidRootPart")

local QuestSystem = {
    CurrentQuest = nil,
    Quests = {
        {Level = 1, NPC = "QuestGiver1", Enemy = "Bandit", Required = 10},
        {Level = 10, NPC = "QuestGiver2", Enemy = "Monkey", Required = 15}
    }
}

function QuestSystem:GetCurrentQuest()
    local playerLevel = LocalPlayer:FindFirstChild("Level") and LocalPlayer.Level.Value or 1
    for _, quest in ipairs(self.Quests) do
        if playerLevel >= quest.Level then
            self.CurrentQuest = quest
        end
    end
    return self.CurrentQuest
end

function QuestSystem:AcceptQuest()
    if not self.CurrentQuest then return end
    local npc = Workspace:FindFirstChild("NPCs") and Workspace.NPCs:FindFirstChild(self.CurrentQuest.NPC)
    if npc then
        LocalPlayer.Character.HumanoidRootPart.CFrame = npc.HumanoidRootPart.CFrame + Vector3.new(0, 3, 0)
        wait(1)
        fireproximityprompt(npc:FindFirstChildOfClass("ProximityPrompt"))
    end
end

local CombatSystem = {
    Target = nil
}

function CombatSystem:FindNearestEnemy()
    local closest = nil
    local maxDist = config.AttackDistance
    local enemies = Workspace:FindFirstChild("Enemies")
    if enemies then
        for _, enemy in ipairs(enemies:GetChildren()) do
            if QuestSystem.CurrentQuest and enemy.Name == QuestSystem.CurrentQuest.Enemy and enemy:FindFirstChild("HumanoidRootPart") then
                local dist = (HumanoidRootPart.Position - enemy.HumanoidRootPart.Position).Magnitude
                if dist < maxDist then
                    closest = enemy
                    maxDist = dist
                end
            end
        end
    end
    return closest
end

function CombatSystem:MeleeAttack()
    if not self.Target then return end
    local tool = Character:FindFirstChildOfClass("Tool")
    if tool then
        tool:Activate()
    end
end

local FlySystem = {}

function FlySystem:MaintainPosition(target)
    local targetPos = target.HumanoidRootPart.Position + Vector3.new(0, config.FlyHeight, 0)
    HumanoidRootPart.CFrame = CFrame.new(HumanoidRootPart.Position:Lerp(targetPos, 0.1))
end

local running = false

local function AutoFarm()
    while running do
        QuestSystem:GetCurrentQuest()
        if QuestSystem.CurrentQuest then
            QuestSystem:AcceptQuest()
            local questCompleted = false
            local defeated = 0
            while not questCompleted and running do
                local enemy = CombatSystem:FindNearestEnemy()
                if enemy then
                    FlySystem:MaintainPosition(enemy)
                    CombatSystem.Target = enemy
                    CombatSystem:MeleeAttack()
                    wait(config.AttackDelay)
                    if not enemy.Parent then
                        defeated = defeated + 1
                    end
                else
                    wait(0.5)
                end
                if defeated >= QuestSystem.CurrentQuest.Required then
                    QuestSystem.CurrentQuest = nil
                    questCompleted = true
                end
            end
        else
            wait(1)
        end
    end
end

local ScreenGui = Instance.new("ScreenGui", game.CoreGui)
local Button = Instance.new("TextButton", ScreenGui)
Button.Size = UDim2.new(0, 200, 0, 50)
Button.Position = UDim2.new(0.5, -100, 0.9, -25)
Button.Text = "Ativar AutoFarm"
Button.BackgroundColor3 = Color3.fromRGB(0, 170, 255)
Button.TextColor3 = Color3.new(1, 1, 1)
Button.TextScaled = true

Button.MouseButton1Click:Connect(function()
    running = not running
    if running then
        Button.Text = "AutoFarm Ativo"
        Button.BackgroundColor3 = Color3.fromRGB(0, 255, 0)
        spawn(AutoFarm)
    else
        Button.Text = "Ativar AutoFarm"
        Button.BackgroundColor3 = Color3.fromRGB(0, 170, 255)
    end
end)
