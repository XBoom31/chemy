#ifndef VARS_H
#define VARS_H

#include "utils.h"
#include "vis3d.h"

struct vvars{
    element tabel[120];
    int current_element;
    int bx,by;
    int selected_element;
    QColor ecol;
    //vis3d vizualizator3d;
};
extern vvars vars;

#endif // VARS_H
