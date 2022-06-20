//
// Created by Иван Ильин on 14.03.2021.
//

#include "Player.h"
#include "engine/utils/Log.h"

Player::Player() : 
RigidBody(Mesh::Cube(ObjectNameTag("Player"))) {
    // TODO: implement (lesson 2)
    setAcceleration(Vec3D(0, -MinecraftConsts::GRAVITY*MinecraftConsts::WORLD_SCALE, 0));
    setCollision(true);
    setColor({240,158,168});
    setVisible(false);
    scale(Vec3D(1.5, 2.8, 1.5));
    //recalculateHitBox();
}

void Player::nextBlock() {
    // TODO: implement (lesson 2)
    _selectedBlock = static_cast<Cube::Type>(((int)_selectedBlock + 1) % (int)Cube::none);
}

void Player::previousBlock() {
    // TODO: implement (lesson 2)
    if((int) _selectedBlock > 0) {
        _selectedBlock = static_cast<Cube::Type>(((int)_selectedBlock - 1) % (int)Cube::none);
    } else {
        _selectedBlock = static_cast<Cube::Type>((int)Cube::none - 1);
    }
    
}

void Player::collisionCallBack(const CollisionInfo &info) {
    // setting vertical velocity to zero after collision

    Vec3D velocity_parallel = info.normal * velocity().dot(info.normal);
    Vec3D velocity_perpendicular = velocity() - velocity_parallel;

    if (velocity().dot(info.normal) > 0) {
        setVelocity(velocity_perpendicular);
    }
}
