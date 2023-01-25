settings = UserSettings.Instance()
stateMaschine = StateMaschine.Instance()
game = Game.Instance()



function Update ()

end


function Draw()

end

function GetText ()
    print "test.lua wurde betreten"
    return ("Hallo ich bin ein test Dialog!\nZeile 2\nZeile 3\nZeile 4 \nUnd ende!")
end
