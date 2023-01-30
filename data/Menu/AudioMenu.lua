MENUID = "AudioMenu"
settings = UserSettings.Instance()
stateMaschine = StateMaschine.Instance()
game = Game.Instance()

ButtonX = settings:GetWindowWidth() / 3
ButtonY = settings:GetWindowHeight() / 7

musicVol = settings:GetMusicVolume()
effectVol = settings:GetEffectVolume()

musicSlider = Slider.new("Musik", ButtonX, ButtonY, ButtonX, ButtonY, musicVol, 0, 1)
effectSlider = Slider.new("Effecte", ButtonX, ButtonY * 3, ButtonX, ButtonY, effectVol, 0, 1)
exitButton = Button.new("Zurueck", ButtonX, ButtonY * 5, ButtonX, ButtonY)

MenuPos = 0;

function Update ()
   -- test(MenuPos)
    if MenuPos == 0
    then
        musicSlider:SetActiv(false)
        effectSlider:SetActiv(true)
        exitButton:SetActiv(false)
    end
    if MenuPos == 1
    then
        musicSlider:SetActiv(true)
        effectSlider:SetActiv(false)
        exitButton:SetActiv(false)
    end
    if MenuPos == 2
    then
        musicSlider:SetActiv(true)
        effectSlider:SetActiv(true)
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
    musicSlider:Resize(ButtonX, ButtonY, ButtonX, ButtonY)
    effectSlider:Resize(ButtonX, ButtonY * 3, ButtonX, ButtonY)
    exitButton:Resize(ButtonX, ButtonY * 5, ButtonX, ButtonY)

end

function Resize ()
    ButtonX = game:GetWindowWidth() / 3
    ButtonY = game:GetWindowHeight() / 7

    musicSlider:Resize(ButtonX, ButtonY, ButtonX, ButtonY)
    effectSlider:Resize(ButtonX, ButtonY * 3, ButtonX, ButtonY)
    exitButton:Resize(ButtonX, ButtonY * 5, ButtonX, ButtonY)
end

function Draw ()
    musicSlider:Draw()
    effectSlider:Draw()
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
    if MenuPos == 0
    then
        if musicVol > 0.0
        then
            musicVol = musicVol - 0.1
            musicSlider:SetValue(musicVol)
            settings:SetMusicVolume(musicVol)
        end
    end

    if MenuPos == 1
    then
        if effectVol > 0.0
        then
            effectVol = effectVol - 0.1
            effectSlider:SetValue(effectVol)
            settings:SetEffectVolume(effectVol)
        end
    end
end

function Key_Right ()
    if MenuPos == 0
    then
        if musicVol < 1.0
        then
            musicVol = musicVol + 0.05
            musicSlider:SetValue(musicVol)
            settings:SetMusicVolume(musicVol)
        end
    end
    if MenuPos == 1
    then
        if effectVol < 1.0
        then
            effectVol = effectVol + 0.05
            effectSlider:SetValue(effectVol)
            settings:SetEffectVolume(effectVol)
        end
    end
end

function Activate ()
    if MenuPos == 2
    then
        stateMaschine:PopState()
    end
end

function Back ()
    stateMaschine:PopState()
end
