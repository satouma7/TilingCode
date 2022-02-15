/*
 *  MacroStructFunction.h
 *  Type0
 *
 *  Created by masakazu on 09/05/22.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#define PI    (3.14159265358979)

#ifdef __cplusplus
#define  Real1(name,i_size)                     double (* (name));(name) = (double (*))malloc(sizeof(double) * (i_size));
#define  Real2(name,i_size,j_size)              double (* (name))[(j_size)];(name) = (double (*)[(j_size)])malloc(sizeof(double) * (i_size) * (j_size));
#define  Real3(name,i_size,j_size,k_size)       double (* (name))[(j_size)][(k_size)];(name) = (double (*)[(j_size)][(k_size)])malloc(sizeof(double) * (i_size) * (j_size) * (k_size));
#else
#define  Real1(name,i_size)                     double (* restrict (name));(name) = (double (* restrict))malloc(sizeof(double) * (i_size));
#define  Real2(name,i_size,j_size)              double (* restrict (name))[(j_size)];(name) = (double (* restrict)[(j_size)])malloc(sizeof(double) * (i_size) * (j_size));
#define  Real3(name,i_size,j_size,k_size)       double (* restrict (name))[(j_size)][(k_size)];(name) = (double (* restrict)[(j_size)][(k_size)])malloc(sizeof(double) * (i_size) * (j_size) * (k_size));
#endif

#define    MyDef(size,name)            double    *name;(name) = (double *) malloc (sizeof(double) * (size));
#define MYDBG    printf("Error = %d\n",__LINE__)

#define SQ(i)                        ((i) * (i))
#define WINDOW_SIZE_X               (1400)
#define WINDOW_SIZE_Y               (1000)
#define WINDOW_POS_X                (0)
#define WINDOW_POS_Y                (0)
#define IG                          (20)
#define INTV                        (100000)
#define XLEN                        (500.0)
#define YLEN                        (500.0)
#define ZLEN                        (2.0)

typedef struct
{
    double r,g,b,a;
} ColorStruct;

typedef struct
{
    int index[6], index_num;
    double ideal_volume, real_volume, EdgeRatio;
    int EdgeRatioFlag;
    Vector2D centroid;
    ColorStruct color;
    
} CellStruct;

typedef struct
{
    int flag;
    //0は孤立した頂点
    //1は1つの細胞に接した頂点
    //2は2つの細胞に接した頂点
    //3は3つの細胞に接した頂点
    
    int Boundaryflag;
    //0は内部，1は上下の境界
    Vector2D r;
    Vector2D destination;
    Vector2D f_length;
    Vector2D f_volume;
    Vector2D f_random;
    Vector2D f_out;
    Vector2D f;

} VertexStruct;

VertexStruct *Vertex,*VertexOld;
CellStruct *Cell,*CellInit;


double Kernel(Vector2D r)
{
    return exp(-SQ(~r)) / PI;
}
Vector2D Vector3DtoVector2D(Vector3D u)
{
    Vector2D ans;
    ans.x = u.x;
    ans.y = u.y;
    return ans;
}

void g_marker_3Ds(Vector3D u) {g_marker_3D(u.x, u.y, u.z);}
void g_polygon_2Ds(Vector2D *u, int n, int Wire,int Fill)
{
    double *x,*y;
    x = (double *) malloc(sizeof(double) * n);
    y = (double *) malloc(sizeof(double) * n);

    for(int i = 0;i < n;i ++)
    {
        x[i] = u[i].x;
        y[i] = u[i].y;
    }
    g_polygon_2D(x, y, n, Wire,Fill);

    free(x);
    free(y);
}
double theta_cut_off(double theta)
{
    while (theta < 0) theta += 2 * PI;
    while (2 * PI < theta )theta -= 2 * PI;
    return theta;
}
Vector2D theta2vec(double theta)
{
    Vector2D u = {cos(theta),sin(theta)};
    return u;
}
void g_move_2Ds(Vector2D r){g_move_2D(r.x, r.y);}
void g_plot_2Ds(Vector2D r){g_plot_2D(r.x, r.y);}

void g_move_3Ds(Vector3D r){g_move_3D(r.x, r.y, r.z);}
void g_plot_3Ds(Vector3D r){g_plot_3D(r.x, r.y, r.z);}

void g_arrow_3Ds(Vector3D r,Vector3D d,double arrow_size,double head_size,int type)
{
    g_arrow_2D(r.x, r.y, d.x, d.y,arrow_size , head_size, type);
}
Vector3D SubsVector(double x,double y,double z)
{
    Vector3D u;u.x = x;u.y = y;u.z = z;
    return u;
}


double  genrand64_Gauss(double mu,double sigma)
{
    double z = sqrt(-2.0 * log(genrand64_real3())) * sin(2.0 * (3.14159265358979) * genrand64_real3());
    return mu + sigma * z;
}

Vector3D RandomForce(double mu,double sigma)
{
    Vector3D u;

    u.x = genrand64_Gauss(mu,sigma);
    u.y = genrand64_Gauss(mu,sigma);
    u.z = genrand64_Gauss(mu,sigma);

    return u;
}
void My_g_box_2D(double xleft, double xright,
                 double ybottom, double ytop)
{
    g_move_2D(xleft, ybottom);
    g_plot_2D(xright,ybottom);
    g_plot_2D(xright,ytop);
    g_plot_2D(xleft,ytop);
    g_plot_2D(xleft,ybottom);
}

void g_arrow_2Ds(Vector2D r,Vector2D d,double arrow_size,double head_size,int type)
{
    g_arrow_2D(r.x, r.y, d.x, d.y,arrow_size , head_size, type);
}

double Myatan2(Vector3D u)
{
    double ans = atan2(u.y, u.x);
    if(ans < 0) ans += 2 * PI;
    return ans;
}

Vector3D R2_to_R3(Vector2D u)
{
    Vector3D w;
    w.x = u.x;
    w.y = u.y;
    w.z = 0;
    return w;
}
Vector2D R3_to_R2(Vector3D u)
{
    Vector2D w;
    w.x = u.x;
    w.y = u.y;
    if(fabs(u.z) > 0.01)
    {
        printf("Function R3_to_R2\n");
    }
    return w;
}

//#define Array(i,j)        (Array[(j) * Imax + (i)])
//void g_color_map(double *Array,
//                 double dx_width, double dy_width,
//                 double L_bottom_x, double L_bottom_y,
//                 double max, double min
//                 )
//{
//    int Fine_Grid = 1;
//    for (int j=0; j < Jmax; j++) {
//        for (int i=0; i < Imax; i++) {
//            if (Fine_Grid == 0) {
//                g_area_color((Array(i,j)-min)/(max-min), 0, 1.0-(Array(i,j)-min)/(max-min), 0.5);
//                g_box_center_2D(dx_width * (i) + L_bottom_x, dy_width * (j) + L_bottom_y, dx_width, dy_width, G_NO, G_YES);
//            }
//
//            if (Fine_Grid == 1) {
//                double tmpColor;
//                if (j-1<0) tmpColor = Array(i,j);
//                else tmpColor = Array(i,j)*0.5 + Array(i,j-1)*0.5;
//                g_area_color((tmpColor-min)/(max-min), 0, 1.0-(tmpColor-min)/(max-min), 1);
//                g_triangle_2D(dx_width * (i) + L_bottom_x, dy_width * (j) + L_bottom_y,
//                              dx_width * (i) + L_bottom_x - dx_width*0.5, dy_width * (j) + L_bottom_y - dy_width*0.5,
//                              dx_width * (i) + L_bottom_x + dx_width*0.5, dy_width * (j) + L_bottom_y - dy_width*0.5,
//                              G_NO, G_YES);
//
//                if (i+1>=Imax) tmpColor = Array(i,j);
//                else tmpColor = Array(i,j)*0.5 + Array(i+1,j)*0.5;
//                g_area_color((tmpColor-min)/(max-min), 0, 1.0-(tmpColor-min)/(max-min), 1);
//                g_triangle_2D(dx_width * (i) + L_bottom_x, dy_width * (j) + L_bottom_y,
//                              dx_width * (i) + L_bottom_x + dx_width*0.5, dy_width * (j) + L_bottom_y - dy_width*0.5,
//                              dx_width * (i) + L_bottom_x + dx_width*0.5, dy_width * (j) + L_bottom_y + dy_width*0.5,
//                              G_NO, G_YES);
//
//                if (j+1>=Jmax) tmpColor = Array(i,j);
//                else tmpColor = Array(i,j)*0.5 + Array(i,j+1)*0.5;
//                g_area_color((tmpColor-min)/(max-min), 0, 1.0-(tmpColor-min)/(max-min), 1);
//                g_triangle_2D(dx_width * (i) + L_bottom_x, dy_width * (j) + L_bottom_y,
//                              dx_width * (i) + L_bottom_x + dx_width*0.5, dy_width * (j) + L_bottom_y + dy_width*0.5,
//                              dx_width * (i) + L_bottom_x - dx_width*0.5, dy_width * (j) + L_bottom_y + dy_width*0.5,
//                              G_NO, G_YES);
//
//                if (i-1<0) tmpColor = Array(i,j);
//                else tmpColor = Array(i,j)*0.5 + Array(i-1,j)*0.5;
//                g_area_color((tmpColor-min)/(max-min), 0, 1.0-(tmpColor-min)/(max-min), 1);
//                g_triangle_2D(dx_width * (i) + L_bottom_x, dy_width * (j) + L_bottom_y,
//                              dx_width * (i) + L_bottom_x - dx_width*0.5, dy_width * (j) + L_bottom_y + dy_width*0.5,
//                              dx_width * (i) + L_bottom_x - dx_width*0.5, dy_width * (j) + L_bottom_y - dy_width*0.5,
//                              G_NO, G_YES);
//            }
//        }
//    }
//}
