/*
 * libEric
 * Copyright (C) 2022   Frank Kartheuser <frank.kartheuser1988@gmail.com>
 * Copyright (C) 2023   Frank Kartheuser <frank.kartheuser1988@gmail.com>
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

#include <tinyxml2.h>
#include <zlib.h>
#include <Config.hpp>
#include "base64.h"
#include "Game.hpp"
#include "GameObjectFactory.hpp"
#include "GraphicGameObject.hpp"
#include "Log.hpp"
#include "MapParser.hpp"
#include "ObjectLayer.hpp"
#include "RenderManager.hpp"
#include "TileLayer.hpp"
#include "../Extra/raylib-physfs.h"
//#include <asm-generic/errno.h>


LibEric::Map* LibEric::MapParser::ParseMap(std::string mapName) {

    LOGI ("Lade Karte: ", mapName);
    std::string mapPath = std::string ("/system/Maps/") + mapName + std::string ("/");
    std::string mapFile = mapPath + std::string ("map.tmx");
    LOGI("Datei: ", mapFile);

    //tinyXML2 daten initialisieren
    tinyxml2::XMLDocument levelDocument;
    tinyxml2::XMLError eResult = levelDocument.Parse(LoadFileTextFromPhysFS(mapFile.c_str()));

//    tinyxml2::XMLError eResult = levelDocument.LoadFile(levelFile.c_str());


    if (eResult != tinyxml2::XML_SUCCESS)
        LOGE ("\tKonnte die Datei nicht laden: ", eResult);

    //Neues MapObjekt erstellen
    Map* newMap = new Map();

    //Anfang des XML-Dokumentes finden
    tinyxml2::XMLElement* root = levelDocument.RootElement();

    //Größe in Pixel, der einzelnen Tiles
    _TileSize = root->IntAttribute("tilewidth");
    LOGV ("Tilebreite: ", _TileSize);
    //Breite der Karte in anzahl der Tiles
    _Width = root->IntAttribute("width");
    //Berechnen der Levelbreite in Pixel
    newMap->_Width = _TileSize*_Width;
    LOGV ("Breite: ", _Width, " Blöcke");
    LOGV ("Breite: ", newMap->_Width, " Pixel");
    //Höhe der Karte in Anzahl der Tiles
    _Height = root->IntAttribute("height");
    //Berechnen der Levelhöhe in Pixel
    newMap->_Height = _TileSize*_Height;
    LOGV ("Höhe: ", _Height, " Blöcke");
    LOGV ("Höhe: ", newMap->_Height, " Pixel");


    //Die einzelnen Elemente der XML-Datei durchgehen
    for(tinyxml2::XMLElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        //tilesets Parsen
        if (std::string(e->Value()) == std::string("tileset")) {
            ParseTilesets(e, newMap->GetTilesets(), std::string("Maps/")+mapName+std::string("/") );
        }
        //die einzelnen Ebenen der Karte laden
        else if (std::string(e->Value()) == std::string("layer")) {
            if(e->FirstChildElement()->Value() == std::string("data") ||
                    (e->FirstChildElement()->NextSiblingElement() != 0 && e->FirstChildElement()->NextSiblingElement()->Value() == std::string("data")))
            {
                ParseTileLayer(e, newMap);
            }
        }
        //die Objekte auf der Karte laden
        else if (std::string(e->Value()) == std::string("objectgroup")) {
            LOGD ("test rrrr");
            if(e->FirstChildElement()->Value() == std::string("object")) {
                LOGD ("Test");
                ParseObjectLayer(e, newMap);
            }
            LOGI("HIER");
        }
    }
    return newMap;
}


void LibEric::MapParser::ParseTilesets(tinyxml2::XMLElement* tilesetRoot, std::vector<Tileset>* tilesets, std::string path) {
    //add tileset to texturemanager
    LOGD ("Parse Tileset: ", tilesetRoot->Attribute("name"));
    std::string tileFile = path + std::string (tilesetRoot->FirstChildElement()->Attribute("source"));
    RenderManager::Instance()->LoadTextureFromFile(tilesetRoot->Attribute("name"),tileFile);

    Tileset tileset;
    tileset.width = tilesetRoot->FirstChildElement()->IntAttribute("width");
    LOGD ("\tBreite        : ", tileset.width);
    tileset.height = tilesetRoot->FirstChildElement()->IntAttribute("height");
    LOGD ("\tHöhe          : ", tileset.height);
    tileset.firstGridID = tilesetRoot->IntAttribute("firstgid");
    LOGD ("\tErstes Element: ", tileset.firstGridID);
    tileset.tileWidth = tilesetRoot->IntAttribute("tilewidth");
    //PLOGD << "\tTile Breite   : " << tileset.tileWidth;
    tileset.tileHeight = tilesetRoot->IntAttribute("tileheight");
    //PLOGD << "\tTile Höhe     : " << tileset.tileHeight;
    tileset.spacing = tilesetRoot->IntAttribute("spacing", 0);
    //PLOGD << "\tSpacing       : " << tileset.spacing;
    tileset.margin = tilesetRoot->IntAttribute("margin", 0);
    //PLOGD << "\tMargin        : " << tileset.margin;
    tileset.name = tilesetRoot->Attribute("name");
    //PLOGD << "\tName          : " << tileset.name;
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);
    //PLOGD << "\tNumColumns    : " << tileset.numColumns;
    tilesets->push_back(tileset);

}

void LibEric::MapParser::ParseTileLayer(tinyxml2::XMLElement* tileElement, Map *rmap) {
    TileLayer* tileLayer = new TileLayer(_TileSize, _Width, _Height, *rmap->GetTilesets() /*tilesets*/);

    std::vector<std::vector<int>> data;

    std::string decodedIDs;
    tinyxml2::XMLElement *dataNode;

    tileLayer->SetName(tileElement->Attribute("name"));
    for (tinyxml2::XMLElement* e = tileElement->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (std::string(e->Value()) == std::string("data")) {
            dataNode = e;
        }
    }

    for (tinyxml2::XMLNode *e = dataNode->FirstChild(); e != nullptr; e = e->NextSibling()) {
        tinyxml2::XMLText *text = e->ToText();
        std::string t = text->Value();
        decodedIDs = base64_decode(t.c_str());
    }

    uLongf numGrids = _Width * _Height * sizeof(int);
    std::vector<unsigned> gids(numGrids);
    uncompress((Bytef*)&gids[0], &numGrids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());

    std::vector<int> layerRow(_Width);

    for (int j = 0; j < _Height; j++) {
        data.push_back(layerRow);
    }

    for (int rows = 0; rows < _Height; rows++) {
        for ( int cols = 0; cols < _Width; cols++) {
            data[rows][cols] = gids[rows *_Width + cols];
        }
    }

    tileLayer->SetTileIDs(data);
    if (std::string(tileElement->Attribute("name")) == std::string ("Background")) {
        rmap->_BackgroundLayer = tileLayer;
    }
    if (std::string(tileElement->Attribute("name")) == std::string ("Road")) {
        rmap->_RoadLayer = tileLayer;
    }
    if (std::string(tileElement->Attribute("name")) == std::string ("Water")) {
        rmap->_WaterLayer = tileLayer;
    }
    if (std::string(tileElement->Attribute("name")) == std::string ("Collision")) {
        rmap->_CollisionLayer = tileLayer;
    }
    if (std::string(tileElement->Attribute("name")) == std::string ("Sky")) {
        rmap->_SkyLayer = tileLayer;
    }

    rmap->GetLayers()->push_back(tileLayer);
}


void LibEric::MapParser::ParseObjectLayer(tinyxml2::XMLElement* pObjectElement, Map* rmap) {
    ObjectLayer* objectLayer = new ObjectLayer();

    for (tinyxml2::XMLElement* e = pObjectElement->FirstChildElement(); nullptr != e; e = e->NextSiblingElement()){
        if (std::string("object") == e->Value()) {
            std::string type = e->Attribute("class");
            GameObject_Interface* gameObject = GameObjectFactory::Instance()->Create(type);
      //      PLOGD << "Parse Objektklasse: " << e->Attribute("class");
            if (gameObject == nullptr) {
                ;//PLOGE << "Konnte Gameobject nicht erstellen: ";
            }
            else {
                int x = 0;
                int y = 0;
                int width = 0;
                int height = 0;
                std::string scriptFile;
                x = e->IntAttribute("x");
                y = e->IntAttribute("y");
                width = e->IntAttribute("width");
                height = e->IntAttribute("height");
                //PLOGD << "\tPosition: " << x << "x" << y;
                //PLOGD << "\tGröße: " << width << "x" << height;
                std::string name = e->Attribute("name");
                //PLOGD << "\tName: " << name;
                for (tinyxml2::XMLElement* properties = e->FirstChildElement(); nullptr != properties; properties = properties->NextSiblingElement()){
                    if (std::string("properties") == properties->Value()){
                        for (tinyxml2::XMLElement* property = properties->FirstChildElement(); nullptr != property; property = property->NextSiblingElement()){
                            if (std::string("script") == property->Attribute("name")) {
                                scriptFile = std::string("scripts/") + property->Attribute("value");
                            }
                        }
                    }

                    //PLOGI << "Lade GameObject_Interface: " << name << " aus lua-script: " <<  scriptFile;
                    //PLOGI << "An Position    : " << x << "x" << y;
                    //PLOGI << "Brite          : " << width;
                    //PLOGI << "Höhe           : " << height;
                    GraphicGameObject *ggo;
                    ggo = (LibEric::GraphicGameObject*)gameObject;
                    ggo->SetPosition(x, y);
                    ggo->SetWidth(width);
                    ggo->SetHeight(height);
                    ggo->Load(scriptFile);

                    objectLayer->GetGameObjectList()->push_back(gameObject);
                }
            }
        }
    }
    rmap->GetLayers()->push_back(objectLayer);
    rmap->_ObjectLayer = objectLayer;
}


