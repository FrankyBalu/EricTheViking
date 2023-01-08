MENUID = "MainMenu"

settings = Settings.Instance()
stateMaschine = StateMaschine.Instance()
game = Game.Instance()

ButtonX = settings:GetWindowWidth() / 3
ButtonY = settings:GetWindowHeight() / 7

newGameButton = Button.new("Neues Spiel", ButtonX, ButtonY, ButtonX, ButtonY)
settingsButton = Button.new("Einstellungen", ButtonX, ButtonY * 3, ButtonX, ButtonY)
exitButton = Button.new("Beenden", ButtonX, ButtonY * 5, ButtonX, ButtonY)


MenuPos = 0;

function Update ()
   -- test(MenuPos)
    if MenuPos == 0
    then
        newGameButton:SetActiv(true)
        settingsButton:SetActiv(false)
        exitButton:SetActiv(false)
    end
    if MenuPos == 1
    then
        newGameButton:SetActiv(false)
        settingsButton:SetActiv(true)
        exitButton:SetActiv(false)
    end
    if MenuPos == 2
    then
        newGameButton:SetActiv(false)
        settingsButton:SetActiv(false)
        exitButton:SetActiv(true)
    end

    if game:IsFS() == false
    then
        ButtonX = settings:GetWindowWidth() / 3
        ButtonY = settings:GetWindowHeight() / 7
    else
        ButtonX = settings:GetFSWidth() / 3
        ButtonY = settings:GetFSHeight() / 7
    end
    newGameButton:Resize(ButtonX, ButtonY, ButtonX, ButtonY)
    settingsButton:Resize(ButtonX, ButtonY * 3, ButtonX, ButtonY)
    exitButton:Resize(ButtonX, ButtonY * 5, ButtonX, ButtonY)

end

function Draw ()
    newGameButton:Draw()
    settingsButton:Draw()
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
        game:Quit()
    end
    if MenuPos == 1
    then
        stateMaschine:PushState ("Menu", "Settings.menu")
    end
    if MenuPos == 0
    then
        stateMaschine:ChangeState ("Play", "egal")
    end

end

function Back ()
    return MenuPos
end
