#ifndef VIS3D_H
#define VIS3D_H
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QOrbitCameraController>
#include <QPainter>

class vis3d
{
private:
    Qt3DExtras::Qt3DWindow view;
    Qt3DCore::QEntity *scene;
    Qt3DRender::QCamera *camera;
    Qt3DExtras::QOrbitCameraController *camController;
    //virtual void paintEvent(QPaintEvent *event);
public:

    void create_window();
    Qt3DExtras::Qt3DWindow* get_view();
    Qt3DCore::QEntity *createScene();
};

#endif // VIS3D_H
