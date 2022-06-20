//
// Created by Иван Ильин on 15.03.2021.
//

#include "Map.h"
#include <iostream>
#include <fstream>
#include "engine/utils/Log.h"

void Map::addCube(const Vec3D& pos, Cube::Type t) {
    // TODO: implement (lesson 1)
    std::string name = "Cube_X_" + std::to_string((int)pos.x())
                        + "_Y_" +std::to_string((int)pos.y())
                        + "_Z_" +std::to_string((int)pos.z());
    world->addBody(std::make_shared<Cube>(ObjectNameTag(name), pos, t));
    cubes.insert({name, {t, pos}});                    
}

void Map::addCubeSilent(const Vec3D& pos, Cube::Type t) {
    // TODO: implement (lesson 1)
    std::string name = "Cube_X_" + std::to_string((int)pos.x())
                        + "_Y_" +std::to_string((int)pos.y())
                        + "_Z_" +std::to_string((int)pos.z());
    world->addBodySilent(std::make_shared<Cube>(ObjectNameTag(name), pos, t));
    cubes.insert({name, {t, pos}});                    
}

void Map::removeCube(const Vec3D& pos) {
    // TODO: implement (lesson 1)
    std::string name = "Cube_X_" + std::to_string((int)pos.x())
                        + "_Y_" +std::to_string((int)pos.y())
                        + "_Z_" +std::to_string((int)pos.z());
    world->removeBody(ObjectNameTag(name));
    cubes.erase(name);
}

void Map::saveMap(const std::string& mapName) {
    // TODO: implement (lesson 1)
    std::ofstream outfile(mapName, std::fstream::trunc);

    for (auto& cube : cubes) {
        outfile << cube.second.first << "\t" <<
        (int)cube.second.second.x() << "\t" <<
        (int)cube.second.second.y() << "\t" <<
        (int)cube.second.second.z();
    }

    outfile.close();
}

void Map::loadMap(const std::string &mapName) {
    // TODO: implement (lesson 1)
    Log::log("Map::loadMap: loading map");
    std::ifstream infile(mapName, std::fstream::out);

    while (!infile.eof()) {
        int t, x, y, z;
        
        infile >> t >> x >> y >> z;
        addCubeSilent(Vec3D(x, y ,z), Cube::Type(t));
    }

    infile.close();
    Log::log("Map::loadMap: map was loaded");
}
