MENUID = "SettingsMenu"
settings = UserSettings.Instance()
game = LibEricApp.Instance()
stateMaschine = StateMaschine.Instance()

ButtonX = settings:GetWindowWidth() / 3
ButtonY = settings:GetWindowHeight() / 7

graphicButton = Button.new("Grafik", ButtonX, ButtonY, ButtonX, ButtonY)
audioButton = Button.new("Audio", ButtonX, ButtonY * 3, ButtonX, ButtonY)
exitButton = Button.new("Zurueck", ButtonX, ButtonY * 5, ButtonX, ButtonY)

MenuPos = 0;

function Update ()
   -- test(MenuPos)
    if MenuPos == 0
    then
        graphicButton:SetActiv(true)
        audioButton:SetActiv(false)
        exitButton:SetActiv(false)
    end
    if MenuPos == 1
    then
        graphicButton:SetActiv(false)
        audioButton:SetActiv(true)
        exitButton:SetActiv(false)
    end
    if MenuPos == 2
    then
        graphicButton:SetActiv(false)
        audioButton:SetActiv(false)
        exitButton:SetActiv(true)
    end
end

function Resize ()
    ButtonX = game:GetWindowWidth() / 3
    ButtonY = game:GetWindowHeight() / 7

    graphicButton:Resize(ButtonX, ButtonY, ButtonX, ButtonY)
    audioButton:Resize(ButtonX, ButtonY * 3, ButtonX, ButtonY)
    exitButton:Resize(ButtonX, ButtonY * 5, ButtonX, ButtonY)
end

function Draw ()
    graphicButton:Draw()
    audioButton:Draw()
    exitButton:Draw()
end

function Key_Up ()
    if MenuPos == 0
    then
        MenuPos = 2
    else
        MenuPos = MenuPos - 1
    end
end

function Key_Down ()
    if MenuPos == 2
    then
        MenuPos = 0
    else
        MenuPos = MenuPos + 1
    end
end

function Key_Left ()

end

function Key_Right ()

end

function Activate ()
    if MenuPos == 2
    then
        stateMaschine:PopState()
    end
    if MenuPos == 1
    then
        stateMaschine:PushState ("Menu", "AudioMenu.lua")
    end
    if MenuPos == 0
    then
        stateMaschine:PushState ("Menu", "GraphicMenu.lua")
    end

end

function Back ()
    PopGameState()
end
