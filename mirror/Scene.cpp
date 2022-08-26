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
    //mNode1->getMaterial(0).EmissiveColor.set(255, 255, 0, 0);
    mNode1->getMaterial(0).EmissiveColor.set(255, 0, 255, 0);
    mNode1->setPosition(core::vector3df(0, 0, 0));

    mNode2 = mSceneManager->addSphereSceneNode(5);
    mNode2->setMaterialFlag(video::EMF_LIGHTING, true);
    mNode2->getMaterial(0).EmissiveColor.set(255, 0, 0, 255);
    mNode2->setPosition(core::vector3df(100, 0, 0));

    //// Add cube
    //mCube = mSceneManager->addCubeSceneNode(40);
    //mCube->setMaterialFlag(video::EMF_LIGHTING, false);
    //mCube->setPosition(core::vector3df(0,0,300));

    // Add plane
    const irr::scene::IGeometryCreator* geomentryCreator = mSceneManager->getGeometryCreator();
    irr::scene::IMesh* planeMesh = geomentryCreator->createPlaneMesh(
        core::dimension2d<irr::f32>(512, 512),
        core::dimension2d<irr::u32>(1, 1)
    );
    planeMesh->setMaterialFlag(video::EMF_LIGHTING, false);
    irr::scene::ISceneNode* mPlane = mSceneManager->addMeshSceneNode(planeMesh);
    //mPlane->getMaterial(0).BackfaceCulling = false;
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
        //core::dimension2d<u32>(512,512),
        "RTT1"
    );
    //mCube->setMaterialTexture(0, mRT);
    mPlane->setMaterialTexture(0, mRT);

    // Add fixed camera
    mFixedCamera = mSceneManager->addCameraSceneNode(
        0,
        core::vector3df(0, 0, 300),
        core::vector3df(0, 0, 0)
    );
    //mFixedCamera->setNearValue(0.001);
    //mFixedCamera->setFarValue(24000);
    //mFixedCamera->setRotation(core::vector3df(90, 0, 0));
}

void Scene::draw() {
    mDriver->beginScene(true, true, video::SColor(0,0,0,0));

    mDriver->setRenderTarget(mRT, true, true, video::SColor(0,0,0,0));
    //mRT->lock(video::ETLM_READ_WRITE, 0, 0, video::ETLF_FLIP_Y_UP_RTT);
    //mRT->unlock();
    //mCube->setVisible(false);
    //mPlane->setVisible(false);
    auto camera = mSceneManager->getActiveCamera();
    //core::matrix4 mat = mFixedCamera->getProjectionMatrix();
    //std::cout << mat[0] << " " << mat[1] << " " << mat[2] << " " << mat[3] << std::endl;
    //std::cout << mat[4] << " " << mat[5] << " " << mat[6] << " " << mat[7] << std::endl;
    //std::cout << mat[8] << " " << mat[9] << " " << mat[10] << " " << mat[11] << std::endl;
    //std::cout << mat[12] << " " << mat[13] << " " << mat[14] << " " << mat[15] << std::endl;
    //std::cout << std::endl;
    core::matrix4 mirror = {
        -1,  0, 0, 0,
         0, -1, 0, 0,
         0,  0, 1, 0,
         0,  0, 0, 1
    };
    mFixedCamera->setViewMatrixAffector(mirror);

    //mat[0] = -mat[0];
    //mat[5] = -mat[5];
    //mat[10] = -mat[10];
    //mat[11] = -mat[11];
    //mat[14] = -mat[14];
    //mat[4] = -mat[4];
    //mat[5] = -mat[5];
    //mat[6] = -mat[6];
    //mat[7] = -mat[7];
    //mFixedCamera->setProjectionMatrix(mat * mirror);
    //mFixedCamera->setProjectionMatrix(mirror * mat);
    
    mSceneManager->setActiveCamera(mFixedCamera);
    mSceneManager->drawAll();
      //mDriver->setRenderTarget(video::ERT_FRAME_BUFFER, true, true, 0);
      //mDriver->setRenderTarget((video::ITexture*) 0, true, true, 0);
      //mDriver->setRenderTarget(0, true, true, video::SColor(0,0,0,255));
    mDriver->setRenderTarget(0, true, true, video::SColor(255,0,0,0));
    //mCube->setVisible(true);
    //mPlane->setVisible(true);
    mSceneManager->setActiveCamera(camera);

    mSceneManager->drawAll();
    mDriver->endScene();
}

void Scene::update(uint32_t dt) {
    core::vector3df pos2 = mNode2->getPosition();

    //auto q = Quaternion::fromAxisAngle(3.1415926 * 2, 0.0, 1.0, 0.0);
    //auto q = Quaternion::fromAxisAngle(0.1, 0.0, 1.0, 1.0);

    auto qx = Quaternion::fromAxisAngle(0.1, 1.0, 0.0, 0.0);
    auto qy = Quaternion::fromAxisAngle(0.1, 0.0, 1.0, 0.0);
    auto qz = Quaternion::fromAxisAngle(0.1, 0.0, 0.0, 1.0);

    //auto qq = q->rotate(pos2.X, pos2.Y, pos2.Z);

    auto q1 = qy->rotate(pos2.X, pos2.Y, pos2.Z);
    //auto q2 = qz->rotate(q1->mX, q1->mY, q1->mZ);

    //pos2.X = q2->mX;
    //pos2.Y = q2->mY;
    //pos2.Z = q2->mZ;
 
    pos2.X = q1->mX;
    pos2.Y = q1->mY;
    pos2.Z = q1->mZ;
 
    //pos2.X = qq->mX;
    //pos2.Y = qq->mY;
    //pos2.Z = qq->mZ;

    mNode2->setPosition(pos2);
}
