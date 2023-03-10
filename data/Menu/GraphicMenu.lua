MENUID = "GraphicMenu"

settings = UserSettings.Instance()
stateMaschine = StateMaschine.Instance()
game = LibEricApp.Instance()

ButtonX = settings:GetWindowWidth() / 3
ButtonY = settings:GetWindowHeight() / 7

colOn = settings:GetCollisionBoxes()

fullscreenBox = CheckBox.new("Vollbild", ButtonX, ButtonY, ButtonY, ButtonY, false)
collisionBox = CheckBox.new("Collisionsbox", ButtonX, ButtonY * 3, ButtonY, ButtonY, colOn)
exitButton = Button.new("Zurueck", ButtonX, ButtonY * 5, ButtonX, ButtonY)

MenuPos = 0;



function Update ()
   -- test für die Größe und Position


   -- test(MenuPos)
    if MenuPos == 0
    then
        fullscreenBox:SetActiv(true)
        collisionBox:SetActiv(false)
        exitButton:SetActiv(false)
    end
    if MenuPos == 1
    then
        fullscreenBox:SetActiv(false)
        collisionBox:SetActiv(true)
        exitButton:SetActiv(false)
    end
    if MenuPos == 2
    then
        fullscreenBox:SetActiv(false)
        collisionBox:SetActiv(false)
        exitButton:SetActiv(true)
    end


end

function Resize ()
    ButtonX = game:GetWindowWidth() / 3
    ButtonY = game:GetWindowHeight() / 7

    fullscreenBox:Resize(ButtonX, ButtonY, ButtonX, ButtonY)
    Collisionsbox:Resize(ButtonX, ButtonY * 3, ButtonX, ButtonY)
    exitButton:Resize(ButtonX, ButtonY * 5, ButtonX, ButtonY)
end

function Draw ()
    fullscreenBox:Draw()
    collisionBox:Draw()
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

    if MenuPos == 0
    then
        b = fullscreenBox:IsActivated()
        if b == true
        then
            fullscreenBox:Toggle(false)
            ButtonX = settings:GetWindowWidth() / 3
            ButtonY = settings:GetWindowHeight() / 7

        else
            fullscreenBox:Toggle(true)
            ButtonX = settings:GetFSWidth() / 3
            ButtonY = settings:GetFSHeight() / 7
        end
        game:ToggleFullscreen()
        fullscreenBox:Resize(ButtonX, ButtonY, ButtonY, ButtonY)
        collisionBox:Resize(ButtonX, ButtonY * 3, ButtonY, ButtonY)
        exitButton:Resize(ButtonX, ButtonY * 5, ButtonX, ButtonY)
    end

    if MenuPos == 1
    then
        b = collisionBox:IsActivated()
        if b == true
        then
            collisionBox:Toggle(false)
            settings:SetCollisionBoxes(false)
        else
            collisionBox:Toggle(true)
            settings:SetCollisionBoxes(true)
        end
    end

end

function Back ()
    stateMaschine:PopState()
end
