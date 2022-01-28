#include "vis3d.h"
#include <QGuiApplication>

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QAspectEngine>

#include <Qt3DInput/QInputAspect>

#include <Qt3DRender/QRenderAspect>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QTorusMesh>

#include <QPropertyAnimation>
#include <Qt3DRender/QParameter>
#include <QEffect>
#include "vars.h"
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QDirectionalLight>

using namespace Qt3DCore;

// vis3d vizualizator3d;

const float rad = 3;
const float volSfera = (4*3.14*rad*rad*rad)/3;
const float padding = 2.5;

static QVector3D shift(0,0,0);
static bool matflip = false;
static bool mad = false;
Qt3DCore::QEntity *createSphere(QVector3D pos, Qt3DRender::QMaterial* material, Qt3DCore::QEntity *rootEntity){
    matflip = !matflip;
    Qt3DCore::QEntity *sphereEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QSphereMesh *sphereMesh = new Qt3DExtras::QSphereMesh;
    sphereMesh->setRadius(rad);
    sphereMesh->setGenerateTangents(true);
    Qt3DCore::QTransform *position = new Qt3DCore::QTransform(sphereEntity);
    position->setTranslation(pos);
    if(mad){
    position->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(), 45));
    }
    Qt3DExtras::QPhongMaterial *torusMaterial = new Qt3DExtras::QPhongMaterial();
    if(matflip)
       torusMaterial->setDiffuse(QColor(QRgb(0xef1f10)));
    else
       torusMaterial->setDiffuse(QColor(QRgb(0xbeb32b)));
    sphereEntity->addComponent(position);
    sphereEntity->addComponent(sphereMesh);
    sphereEntity->addComponent(torusMaterial);
    return sphereEntity;
}


//short for createSphere
#define cS(a) matflip ? createSphere(a,material, rootEntity) : createSphere(a,material2, rootEntity);

Qt3DCore::QEntity *vis3d::createScene()
{
    element x = vars.selected_element ? vars.tabel[vars.selected_element-1] : vars.tabel[vars.selected_element];
    int protons = x.natomic;
    int neutrons = x.atomic_mass - x.natomic;
    int nucleoni = protons + neutrons;

    //daca avem numai un proton si zero neutroni punem in mijloc
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;
    Qt3DRender::QMaterial *material = new Qt3DExtras::QPhongMaterial(rootEntity);
    Qt3DRender::QMaterial *material2 = new Qt3DExtras::QPhongMaterial(rootEntity);
    const QString col = QStringLiteral("color");
    material->addParameter(new Qt3DRender::QParameter(col, QColor::fromRgb(255,255,255)));
    material2->addParameter(new Qt3DRender::QParameter(col, QColor::fromRgbF(0.0f, 1.0f, 0.0f, 1.0f)));

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(rootEntity);
       Qt3DRender::QDirectionalLight *light = new Qt3DRender::QDirectionalLight(lightEntity);
       light->setColor("white");
       light->setIntensity(10);
       lightEntity->addComponent(light);
       Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
       lightTransform->setTranslation(QVector3D(-20, 20, 20));
       lightEntity->addComponent(lightTransform);

    if(!nucleoni)
        return rootEntity;
    if(nucleoni == 1)
        createSphere(QVector3D(0,0,0),material, rootEntity);
    else{
        int xflip = 1;
        QVector3D xpad(padding, 0, 0);
        int yflip = 0;
        QVector3D ypad(0, padding, 0);
        int zflip = 0;
        QVector3D zpad(0, 0, padding);
        int c =0,c2=1;
        for (int i = 0; i < nucleoni; i++){
            switch(c){
            case 0:
                xpad[2] = i%4-padding;
                cS(xpad*c2);
                c++;
                continue;
            case 1:
                ypad[2] = i%4-padding;
                cS(ypad*c2);
                c++;
                continue;
            case 2:
                zpad[0] = i%4-padding;
                cS(zpad*c2);
                c++;
                continue;
            case 3:
                xpad[1] = i%4-padding;
                cS(-xpad*c2);
                c++;
                continue;
            case 4:
                ypad[0] = i%4-padding;
                cS(-ypad*c2);
                c++;
                continue;
            case 5:
                zpad[1] = i%4-padding;
                cS(-zpad*c2);
                c = 0;

                mad = true; //yes
                c2++;
                continue;
            }
        }
    }

    return rootEntity;
}


void vis3d::create_window(){



        scene = createScene();

        // Camera
        camera = view.camera();
        camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
        camera->setPosition(QVector3D(0, 0, 20.0f));
        camera->setViewCenter(QVector3D(0, 0, 0));

        // For camera controls
        camController = new Qt3DExtras::QOrbitCameraController(scene);
        camController->setLinearSpeed( 50.0f );
        camController->setLookSpeed( 180.0f );
        camController->setCamera(camera);
        view.defaultFrameGraph()->setClearColor(QRgb(0x1d1d4f));

        view.setRootEntity(scene);
        //view.show();
}

Qt3DExtras::Qt3DWindow* vis3d::get_view()
{
    return &view;
}
