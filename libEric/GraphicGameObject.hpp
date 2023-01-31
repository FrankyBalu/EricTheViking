/*
 * LibEric
 * Copyright (C) 2022  Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2023  Frank Kartheuser <frank.kartheuser1988@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef __GRAPHICGAMEOBJECT
#define __GRAPHICGAMEOBJECT

#include <libEric/GameObject_Interface.hpp>
#include <raylib.h>


namespace LibEric {

    class GraphicGameObject : public GameObject_Interface {
    public:

        GraphicGameObject();

        //Objektparameter Laden
        virtual void Load(const std::string script);

        //Objekt Darstellen
        virtual void Draw();

        //Logik des Objektes updaten
        virtual void Update();

        //Speicher freigeben
        virtual void Clean();


        //! FIXME erstmal zum testen
        virtual void ObjectCollision(GameObject_Interface *object);

        virtual void CollisionWithMap();

        virtual std::string GetID();

        //Position des Objektes zurückgeben
        Vector2 GetPosition();

        void SetPosition(float x, float y);

        int GetWidth();

        int GetHeight();

        void SetWidth(float w);

        void SetHeight(float h);


        virtual Rectangle GetRect();

    protected:

        int _Width;
        int _Height;

        Vector2 _Position;

        int _CurrentFrame;
        int _CurrentRow;

        std::string _TextureID;

        std::string _TypeID;

        bool _Visable;

    };

}; //namespace LibEric
#endif // __GRAPHICGAMEOBJECT
