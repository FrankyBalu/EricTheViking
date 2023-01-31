-- Name des Menus
MENUID = "MainMenu"

-- GameStateMaschine Instance, um Menüs zu wechseln oder ein Spiel zu starten
stateMaschine = StateMaschine.Instance()
-- Instance von Game, um das Spiel zu beenden
game = Game.Instance()

settings = UserSettings.Instance()

-- X-Position aller Menu Knöpfe
ButtonX = settings:GetWindowWidth() / 3
-- Y-Position des ersten Knöpfes
ButtonY = settings:GetWindowHeight() / 7

-- Knopf für neues Spiel
newGameButton = Button.new("Neues Spiel", ButtonX, ButtonY, ButtonX, ButtonY)
-- Knopf für Optionen
settingsButton = Button.new("Einstellungen", ButtonX, ButtonY * 3, ButtonX, ButtonY)
-- Knopf zum beenden
exitButton = Button.new("Beenden", ButtonX, ButtonY * 5, ButtonX, ButtonY)

-- Positin innerhalb des Menüs
MenuPos = 0;

-- Update Funktion für das Menü
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

    -- Falls der Beenden Dialog mit ja beantwortet wurde, wird das Spiel beendet
    if ExitGame()
    then
        game:Quit()
    end
end

-- Neuberechnung der größe der Elemente, nach ändern der Bildschirmauflösung
function Resize ()
    ButtonX = game:GetWindowWidth() / 3
    ButtonY = game:GetWindowHeight() / 7

    newGameButton:Resize(ButtonX, ButtonY, ButtonX, ButtonY)
    settingsButton:Resize(ButtonX, ButtonY * 3, ButtonX, ButtonY)
    exitButton:Resize(ButtonX, ButtonY * 5, ButtonX, ButtonY)
end


-- Zeichnet alles auf den Bildschirm
function Draw ()
    newGameButton:Draw()
    settingsButton:Draw()
    exitButton:Draw()
end

-- Wenn Richtungstaste nach oben gedrückt wurde
function Key_Up ()
    if MenuPos == 0
    then
        MenuPos = 2
    else
        MenuPos = MenuPos - 1
    end
end

-- Wenn Richtungstaste nach unten gedrückt wurde
function Key_Down ()
    if MenuPos == 2
    then
        MenuPos = 0
    else
        MenuPos = MenuPos + 1
    end
end

-- Wenn Richtungstaste nach links gedrückt wurde
function Key_Left ()

end

-- Wenn Richtungstaste nach rechts gedrückt wurde
function Key_Right ()

end

-- Wenn Aktivierentaste gedrückt wurde
function Activate ()
    if MenuPos == 2
    then
        CreateExitDialog()
    end
    if MenuPos == 1
    then
        stateMaschine:PushState ("Menu", "SettingsMenu.lua")
    end
    if MenuPos == 0
    then
        stateMaschine:ChangeState ("Play", "egal")
    end

end


function Back ()
    return MenuPos
end
