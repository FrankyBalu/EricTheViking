MENUID = "PauseMenu"
settings = UserSettings.Instance()
game = Game.Instance()
stateMaschine = StateMaschine.Instance()

ButtonX = settings:GetWindowWidth() / 3
ButtonY = settings:GetWindowHeight() / 9

resumeButton = Button.new("Weiter Spielen", ButtonX, ButtonY, ButtonX, ButtonY)
settingsButton = Button.new("Einstellungen", ButtonX, ButtonY * 3, ButtonX, ButtonY)
mainmenuButton = Button.new("Hauptmenu", ButtonX, ButtonY * 5, ButtonX, ButtonY)
exitButton = Button.new("Beenden", ButtonX, ButtonY * 7, ButtonX, ButtonY)

MenuPos = 0;

function Update ()
   -- test(MenuPos)
    if MenuPos == 0
    then
        resumeButton:SetActiv(true)
        settingsButton:SetActiv(false)
        mainmenuButton:SetActiv(false)
        exitButton:SetActiv(false)
    end
    if MenuPos == 1
    then
        resumeButton:SetActiv(false)
        settingsButton:SetActiv(true)
        mainmenuButton:SetActiv(false)
        exitButton:SetActiv(false)
    end
    if MenuPos == 2
    then
        resumeButton:SetActiv(false)
        settingsButton:SetActiv(false)
        mainmenuButton:SetActiv(true)
        exitButton:SetActiv(false)
    end
    if MenuPos == 3
    then
        resumeButton:SetActiv(false)
        settingsButton:SetActiv(false)
        mainmenuButton:SetActiv(false)
        exitButton:SetActiv(true)
    end

    if ExitGame()
    then
        game:Quit()
    end
end

function Resize ()
    ButtonX = game:GetWindowWidth() / 3
    ButtonY = game:GetWindowHeight() / 7

    resumeButton:Resize(ButtonX, ButtonY, ButtonX, ButtonY)
    settingsButton:Resize(ButtonX, ButtonY * 3, ButtonX, ButtonY)
    mainmenuButton:Resize(ButtonX, ButtonY * 5, ButtonX, ButtonY)
    exitButton:Resize(ButtonX, ButtonY * 7, ButtonX, ButtonY)
end

function Draw ()
    resumeButton:Draw()
    settingsButton:Draw()
    mainmenuButton:Draw()
    exitButton:Draw()
end

function Key_Up ()
    if MenuPos == 0
    then
        MenuPos = 3
    else
        MenuPos = MenuPos - 1
    end
end

function Key_Down ()
    if MenuPos == 3
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
    if MenuPos == 3
    then
        CreateExitDialog()
    end
    if MenuPos == 2
    then
        stateMaschine:PushState ("Menu", "MainMenu.lua")
    end
    if MenuPos == 1
    then
        stateMaschine:PushState ("Menu", "SettingsMenu.lua")
    end
    if MenuPos == 0
    then
        stateMaschine:PopState ()
    end

end

function Back ()
    return MenuPos
end
