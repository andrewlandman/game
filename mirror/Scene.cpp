#include "Scene.hpp"
#include "Quaternion.hpp"
#include <iostream>

Scene::Scene(scene::ISceneManager* sceneManager,
             video::IVideoDriver*  driver)
    :
    mSceneManager(sceneManager),
    mDriver(driver)
{}

void Scene::initialize() {
    // Add spheres
    mNode1 = mSceneManager->addSphereSceneNode(5);
    mNode1->setMaterialFlag(video::EMF_LIGHTING, true);
    mNode1->getMaterial(0).EmissiveColor.set(255, 0, 255, 0);
    mNode1->setPosition(core::vector3df(0, 0, 0));

    mNode2 = mSceneManager->addSphereSceneNode(5);
    mNode2->setMaterialFlag(video::EMF_LIGHTING, true);
    mNode2->getMaterial(0).EmissiveColor.set(255, 0, 0, 255);
    mNode2->setPosition(core::vector3df(100, 0, 0));

    // Add plane
    const irr::scene::IGeometryCreator* geomentryCreator = mSceneManager->getGeometryCreator();
    irr::scene::IMesh* planeMesh = geomentryCreator->createPlaneMesh(
        core::dimension2d<irr::f32>(512, 512),
        core::dimension2d<irr::u32>(1, 1)
    );
    planeMesh->setMaterialFlag(video::EMF_LIGHTING, false);
    irr::scene::ISceneNode* mPlane = mSceneManager->addMeshSceneNode(planeMesh);
    mPlane->getMaterial(0).BackfaceCulling = true;
    mPlane->setPosition(core::vector3df(0, 0, 300));
    mPlane->setRotation(core::vector3df(90, 0, 0));
    mSceneManager->getMeshManipulator()->flipSurfaces(planeMesh);
    mSceneManager->getMeshManipulator()->recalculateNormals(planeMesh);

    // Add skybox
    scene::IMeshSceneNode* skybox = mSceneManager->addCubeSceneNode(1000);
    skybox->setMaterialFlag(video::EMF_LIGHTING, true);
    skybox->getMaterial(0).EmissiveColor.set(255, 40, 40, 40);
    skybox->getMaterial(0).BackfaceCulling = true;
    skybox->setPosition(core::vector3df(0, 0, 0));
    mSceneManager->getMeshManipulator()->flipSurfaces(skybox->getMesh());
    mSceneManager->getMeshManipulator()->recalculateNormals(skybox->getMesh());

    // Add light
    scene::ISceneNode* light = mSceneManager->addLightSceneNode(
        0,
        core::vector3df(500, 0, 100),
        video::SColorf(1.0, 1.0, 1.0),
        250
    );

    // Add render texture
    mRT = mDriver->addRenderTargetTexture(
        core::dimension2d<u32>(256,256),
        "RTT1"
    );
    mPlane->setMaterialTexture(0, mRT);

    // Add fixed camera
    mFixedCamera = mSceneManager->addCameraSceneNode(
        0,
        core::vector3df(0, 0, 300),
        core::vector3df(0, 0, 0)
    );
}

void Scene::draw() {
    mDriver->beginScene(true, true, video::SColor(0,0,0,0));

    // Draw mirror
    mDriver->setRenderTarget(mRT, true, true, video::SColor(0,0,0,0));
    core::matrix4 mirror = {
        -1,  0, 0, 0,
         0, -1, 0, 0,
         0,  0, 1, 0,
         0,  0, 0, 1
    };
    mFixedCamera->setViewMatrixAffector(mirror);
    auto camera = mSceneManager->getActiveCamera();
    mSceneManager->setActiveCamera(mFixedCamera);
    mSceneManager->drawAll();

    // Draw scene
    mDriver->setRenderTarget(0, true, true, video::SColor(255,0,0,0));
    mSceneManager->setActiveCamera(camera);
    mSceneManager->drawAll();

    mDriver->endScene();
}

void Scene::update(uint32_t dt) {
    core::vector3df pos2 = mNode2->getPosition();

    auto q = Quaternion::fromAxisAngle(0.1, 0.0, 1.0, 0.0);
    q = q->rotate(pos2.X, pos2.Y, pos2.Z);

    pos2.X = q->mX;
    pos2.Y = q->mY;
    pos2.Z = q->mZ;
 
    mNode2->setPosition(pos2);
}
