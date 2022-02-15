
/*
 *  init_glsc.h
 *  Type0
 *
 *  Created by masakazu on 09/05/22.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

g_enable_highdpi();
g_set_antialiasing(4);

g_init_core("GRAPH",
               WINDOW_SIZE_X,
               WINDOW_SIZE_Y,
               WINDOW_POS_X,
               WINDOW_POS_Y,
               1, 1, 1,
               0, 1 << 23, 1 << 23);


if(((int)UseCapture != 0))
{
    g_capture_set(filename);
}

ig = 0;
xleft_std[ig] = 5.0;
ytop_std[ig] = 5.0;
xwid_std[ig] = 900.0;
ywid_std[ig] = 900.0;
xleft[ig] = -XLEN / 2;
xright[ig] = XLEN / 2;
ybottom[ig] = -YLEN / 2;
ytop[ig] = YLEN / 2 ;
zfar[ig] = -ZLEN / 2;
znear[ig] = ZLEN / 2;
direction_x[ig] = 0.5;
direction_y[ig] = 0.5;
direction_z[ig] = 0.7;
EYE_r[ig] = 10 * XLEN;
normal_x[ig] = 0;
normal_y[ig] = 0;
normal_z[ig] = 1;

ig = 1;
xleft_std[ig] = 915.0;
ytop_std[ig] = 600.0;
xwid_std[ig] = 300.0;
ywid_std[ig] = xwid_std[ig];
xleft[ig] = -XLEN / 2;
xright[ig] = XLEN / 2;
ybottom[ig] = -YLEN / 2;
ytop[ig] = YLEN / 2;
zfar[ig] = -ZLEN / 2;
znear[ig] = ZLEN / 2;
direction_x[ig] = 0.5;
direction_y[ig] = 0.5;
direction_z[ig] = 0.7;
EYE_r[ig] = 0;
normal_x[ig] = 0;
normal_y[ig] = 0;
normal_z[ig] = 1;

ig = 2;
xleft_std[ig] = 915.0;
ytop_std[ig] = 500.0;
xwid_std[ig] = 300.0;
ywid_std[ig] = 80.0;
xleft[ig] = 0.2;
xright[ig] = 2.4;
ybottom[ig] = -1;
ytop[ig] = 1;
zfar[ig] = -ZLEN / 2;
znear[ig] = ZLEN / 2;
direction_x[ig] = 0.5;
direction_y[ig] = 0.5;
direction_z[ig] = 0.7;
EYE_r[ig] = 0;
normal_x[ig] = 0;
normal_y[ig] = 0;
normal_z[ig] = 1;

for (ig = 0; ig < 3; ig++)
g_def_scale_2D(ig,
               xleft[ig], xright[ig],
               ybottom[ig], ytop[ig],
               xleft_std[ig], ytop_std[ig], xwid_std[ig], ywid_std[ig]);

//for (ig = 0; ig < 1; ig++)
//{
//    g_def_scale_3D_fix(
//                       ig,
//                       xleft[ig], xright[ig],
//                       ybottom[ig], ytop[ig],
//                       zfar[ig],znear[ig],
//                       xleft_std[ig], ytop_std[ig],
//                       xwid_std[ig], ywid_std[ig]);
//    g_vision(ig,
//             0 * (xright[ig] - xleft[ig]),
//             -2.4 * (ytop[ig] - ybottom[ig]),
//             10000.0  * (znear[ig] - zfar[ig]),
//             0, 0, 1,
//                    1.25);
//}



