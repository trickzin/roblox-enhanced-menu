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

local function log(message)
    if config.DebugMode then
        print("[DEBUG] " .. message)
    end
end

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
    local npc = Workspace.NPCs:FindFirstChild(self.CurrentQuest.NPC)
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
    for _, enemy in ipairs(Workspace.Enemies:GetChildren()) do
        if QuestSystem.CurrentQuest and enemy.Name == QuestSystem.CurrentQuest.Enemy and enemy:FindFirstChild("HumanoidRootPart") then
            local dist = (Character.HumanoidRootPart.Position - enemy.HumanoidRootPart.Position).Magnitude
            if dist < maxDist then
                closest = enemy
                maxDist = dist
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
    local root = Character.HumanoidRootPart
    local targetPos = target.HumanoidRootPart.Position + Vector3.new(0, config.FlyHeight, 0)
    root.CFrame = CFrame.new(root.Position:Lerp(targetPos, 0.1))
end

local running = false

local function AutoFarm()
    running = true
    while running and wait() do
        QuestSystem:GetCurrentQuest()
        if not QuestSystem.CurrentQuest then continue end
        CombatSystem.Target = CombatSystem:FindNearestEnemy()
        if CombatSystem.Target then
            FlySystem:MaintainPosition(CombatSystem.Target)
            CombatSystem:MeleeAttack()
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
    if not running then
        QuestSystem:AcceptQuest()
        AutoFarm()
        Button.Text = "AutoFarm Ativo"
        Button.BackgroundColor3 = Color3.fromRGB(0, 255, 0)
    else
        running = false
        Button.Text = "Ativar AutoFarm"
        Button.BackgroundColor3 = Color3.fromRGB(0, 170, 255)
    end
end)