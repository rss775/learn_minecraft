//
// Created by Иван Ильин on 03.10.2021.
//

#include "Minecraft.h"
#include "engine/ResourceManager.h"

using namespace std;

void Minecraft::start() {
    // This code executed once in the beginning:

    screen->setMouseCursorVisible(false);
    setGlEnable(true);

    // loading map
    // TODO: implement (lesson 1)
    map->loadMap(MinecraftConsts::MAP_NAME);

    // setting callbacks for playerController
    playerController->setAddCubeCallBack([this](){ addCube(); });
    playerController->setRemoveCubeCallBack([this](){ return removeCube(); });
    playerController->setUpdateCubeInHandCallBack([this](){ updateCubeInHandColor(); });
    world->addBody(player);

    // orientating and attaching camera
    // TODO: implement (lesson 2)
    camera->translateToPoint(player->position() + Vec3D(0, 0.8, 0)*MinecraftConsts::WORLD_SCALE);

    player->attach(camera);
    player->translate(Vec3D(0, 2*MinecraftConsts::WORLD_SCALE, 0));

    // adding cube in hand
    // TODO: implement (lesson 2)
    auto cube_in_hand = world->addBody(std::make_shared<RigidBody>(Mesh::Cube(ObjectNameTag("cube_in_hand"), MinecraftConsts::WORLD_SCALE/2)));
    cube_in_hand->setCollider(false);
    cube_in_hand->translateToPoint(player->position() + Vec3D(-1.4,-0.5, 0.7)*MinecraftConsts::WORLD_SCALE);
    cube_in_hand->rotate(Vec3D(0, M_PI/10, 0));

    camera->attach(cube_in_hand);
    updateCubeInHandColor();

    //world->addBody(player);
}

void Minecraft::update() {
    // This code executed every time step:

    // exit the game
    if(keyboard->isKeyTapped(sf::Keyboard::Escape)) {
        exit();
    }

    // switch  OpenGL on/off
    if (keyboard->isKeyTapped(sf::Keyboard::O)) {
        setGlEnable(!glEnable());
    }

    // display debug info
    if (keyboard->isKeyTapped(sf::Keyboard::Tab)) {
        setDebugInfo(!showDebugInfo());
    }

    // save map
    if (keyboard->isKeyTapped(sf::Keyboard::R)) {
        map->saveMap(MinecraftConsts::MAP_NAME);
    }

    playerController->update();

    //cameraController.update();
}

void Minecraft::updateCubeInHandColor() {
    // TODO: implement (lesson 2)
    world->body(ObjectNameTag("cube_in_hand"))->setColor(Cube::cubeColor(player->selectedBlock()));
}

void Minecraft::gui() {
    // TODO: implement (lesson 2)
    auto t = ResourceManager::loadTexture(MinecraftConsts::AIM_TEXTURE);
    if(t != nullptr) {
        sf::Sprite sprite;
        sprite.setTexture(*t);
        sprite.setPosition(screen->width() / 2 -27, screen->height() / 2 - 27);
        sprite.setColor(sf::Color(0, 0, 0, 150));
        screen->drawSprite(sprite);
    }
}

void Minecraft::addCube() {
    // TODO: implement (lesson 3)
    auto rayCast = world->rayCast(camera->position(), camera->position() + camera->lookAt()*10, "Player");
    if((rayCast.pointOfIntersection - camera->position()).abs() < MinecraftConsts::REACH_RANGE * MinecraftConsts::WORLD_SCALE) {
        Vec3D cubePoint = (rayCast.intersectedTriangle.position() + rayCast.intersectedTriangle.norm()*MinecraftConsts::WORLD_SCALE/2);

        map->addCube(Vec3D(round(cubePoint.x()/MinecraftConsts::WORLD_SCALE),
                            round(cubePoint.y()/MinecraftConsts::WORLD_SCALE), 
                            round(cubePoint.z()/MinecraftConsts::WORLD_SCALE)), player->selectedBlock());
    }
}

void Minecraft::removeCube() {
    // TODO: implement (lesson 3)
    auto rayCast = world->rayCast(camera->position(), camera->position() + camera->lookAt()*10, "Player");
    if((rayCast.pointOfIntersection - camera->position()).abs() < MinecraftConsts::REACH_RANGE * MinecraftConsts::WORLD_SCALE) {
        Vec3D cubePoint = (rayCast.intersectedTriangle.position() - rayCast.intersectedTriangle.norm()*MinecraftConsts::WORLD_SCALE/2);

        map->removeCube(Vec3D(round(cubePoint.x()/MinecraftConsts::WORLD_SCALE), 
                                round(cubePoint.y()/MinecraftConsts::WORLD_SCALE), 
                                round(cubePoint.z()/MinecraftConsts::WORLD_SCALE)));
    }
}
