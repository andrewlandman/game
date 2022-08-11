#include "camera.hpp"

Camera::Camera(scene::ISceneManager* sceneManager) {
    mCamera = sceneManager->addCameraSceneNode();

    mNode = sceneManager->addSphereSceneNode();
    mNode->setMaterialFlag(video::EMF_LIGHTING, true);
    mNode->getMaterial(0).EmissiveColor.set(255, 255, 0, 0);
}

void Camera::update(irr::core::vector3df offset) {
    irr::core::matrix4 m;
    m.setRotationDegrees(mNode->getRotation());

    irr::core::vector3df frv = irr::core::vector3df(0.0f, 0.0f, 1.0f);
    m.transformVect(frv);

    irr::core::vector3df upv = irr::core::vector3df(0.0f, 1.0f, 0.0f);
    m.transformVect(upv);

    m.transformVect(offset);

    offset += mNode->getPosition();
    mCamera->setPosition(offset);

    mCamera->setUpVector(upv);

    offset += frv;
    mCamera->setTarget(offset);

    mCamera->updateAbsolutePosition();
}

void Camera::move(irr::core::vector3df vel) {
    irr::core::matrix4 m;
    m.setRotationDegrees(mNode->getRotation());
    m.transformVect(vel);
    mNode->setPosition(mNode->getPosition() + vel);
    mNode->updateAbsolutePosition();
}

void Camera::rotate(irr::core::vector3df rot) {
    irr::core::matrix4 m;
    m.setRotationDegrees(mNode->getRotation());
    irr::core::matrix4 n;
    n.setRotationDegrees(rot);
    m *= n;
    mNode->setRotation(m.getRotationDegrees());
    mNode->updateAbsolutePosition();
}

void Camera::turn(irr::f32 rot) {
    rotate(irr::core::vector3df(0.0f, rot, 0.0f));
}

void Camera::pitch(irr::f32 rot) {
    rotate(irr::core::vector3df(rot, 0.0f, 0.0f));
}

void Camera::roll(irr::f32 rot) {
    rotate(irr::core::vector3df(0.0f, 0.0f, rot));
}
