#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#include<string.h>

#include<basic.h>
#include<VectorStructOperator.h>

/* G.L.S.C. 3D Setting */
#include<glsc3d_3.h>
#define WINDOW_SIZE_X     (512)
#define WINDOW_SIZE_Y     (512)
#define WINDOW_POS_X      (0)
#define WINDOW_POS_Y      (0)

/* Experimental data */
int Input_File_Name = 1;

char type[10];
int Weight_Flag = 0;
int tmp_Weight_Flag = 0;
int File_Name = 0;
int Image_Name = 0;
int Image_Time = 0;
int SiteNumber = 0;
int DrawCellNumber = 0;
int DrawCellLabel[100];

/* Setting */
#define EPS (1.0e-15)

double L = 512;
int N = 512;

double RadiusRate = 10.0; /* Search speed of discrete Voronoi diagram */

typedef struct {
    int label;
    int edgelabel;
    double x;
    double y;
} PixelInfo;

typedef struct {
    int Cell_Number;
    int Pixel_Number;
    Vector2D *Pixel_Position;
} CellPixelInfo;

void Pixel_Position_Init(CellPixelInfo *u) {
    (*u).Pixel_Position = (Vector2D *)malloc(sizeof(Vector2D) * N * N);
}

/* Voronoi setting */
typedef struct {
    double r;
    double g;
    double b;
    double a;
} VoronoiCellColor;

VoronoiCellColor MakeCellColor(int i) {
    VoronoiCellColor Color;
    Color.r = 0.5;
    Color.g = 0.5;
    Color.b = 0.5;
    Color.a = 0.2;
    unsigned long long seed = i;
    init_genrand64(seed);
//    Color.r = genrand64_real2();
//    Color.g = genrand64_real2();
//    Color.b = genrand64_real2();
//    Color.a = 1.0;
    return Color;
}

/* Distance function setting */
int DistanceFunctionMode = 1;
double DistanceFunction(Vector2D a, Vector2D b, int mode) {
    /* Lp distance */
    if (mode == 1) {
        double p = 2;
        return pow(pow(fabs(a.x - b.x), p) + pow(fabs(a.y - b.y), p), 1.0/p);
    }
    
    else {
        return ~(a-b);
    }
}

/* main */
int main(int argc, char *argv[]) {
    
    double dummy = 0.0;
    double tmp_Input_File_Name = 0.0;
    double tmp_Weight_Flag = 0.0;
    GetParam2(argc, argv, 10, &(tmp_Input_File_Name), &(tmp_Weight_Flag), &(dummy), NULL);
    Input_File_Name = (int)tmp_Input_File_Name;
    Weight_Flag = (int)tmp_Weight_Flag;
    printf("Input_File_Name = %d\n", Input_File_Name);
    printf("Weight_Flag = %d\n", Weight_Flag);
    
    if (Input_File_Name == 0) {
        printf("Input your file name\n");
        exit(0);
    }
    
    /* Input Data */
    #include "experiment_database.c"
    printf("Type = %s\n", type);
    printf("Weight = %d\n", Weight_Flag);
    printf("Image_Name = %d\n", Image_Name);
    printf("Image_Time = %d\n", Image_Time);
    printf("SiteNumber = %d\n", SiteNumber);
    printf("DrawNumber = %d\n", DrawCellNumber);

    double dx = L / N;
    double dy = L / N;
    
    FILE *fp;
    char FileName[256];
    
    /* Sites of Voronoi diagram */
    Vector2D *Site;
    Site = (Vector2D *)malloc(sizeof(Vector2D) * SiteNumber);
    double SiteSize = 2.0;

    /* Initial position of sites */
    sprintf(FileName, "./Vertex_%d.dat", File_Name);
    fp=fopen(FileName, "r");
    for (int i=0; i<SiteNumber; i++){
        fscanf(fp, "%lf %lf\n", &Site[i].x, &Site[i].y);
    }
    fclose(fp);

    /* Weight Preparation */
    double *Weight;
    Weight = (double *)malloc(sizeof(double) * SiteNumber);
    if (Weight_Flag == 1) {
        sprintf(FileName, "./Weight_%d.dat", File_Name);
        fp=fopen(FileName, "r");
        for (int i=0; i<SiteNumber; i++){
            fscanf(fp, "%lf\n", &Weight[i]);
        }
        fclose(fp);
    } else {
        for (int i=0; i<SiteNumber; i++){
            Weight[i] = 1.0;
        }
    }
    
    /* Voronoi setting */
    VoronoiCellColor *CellColor;
    CellColor = (VoronoiCellColor *)malloc(sizeof(VoronoiCellColor) * SiteNumber);
    for (int i=0; i<SiteNumber; i++) {
        CellColor[i] = {MakeCellColor(i).r, MakeCellColor(i).g, MakeCellColor(i).b, 1.0};
    }
    
    /* Pixel setting */
    PixelInfo *Pixel;
    Pixel = (PixelInfo *)malloc(sizeof(PixelInfo) * N * N);
    CellPixelInfo *CellPixel;
    CellPixel = (CellPixelInfo *)malloc(sizeof(CellPixelInfo) * SiteNumber);
    for (int i=0; i<SiteNumber; i++) {
        CellPixel[i].Cell_Number = i;
        CellPixel[i].Pixel_Number = 0;
        Pixel_Position_Init(&CellPixel[i]);
    }
    for (int j=0; j<N; j++) {
        for (int i=0; i<N; i++) {
            Pixel[i + N * j].x = 0.0;
            Pixel[i + N * j].y = 0.0;
            Pixel[i + N * j].label = -2;
            
            CellColor[Pixel[i + N * j].label].r = 1.0;
            CellColor[Pixel[i + N * j].label].g = 1.0;
            CellColor[Pixel[i + N * j].label].b = 1.0;
            CellColor[Pixel[i + N * j].label].a = 1.0;
        }
    }
    
    /* G.L.S.C 3D */
//    g_enable_highdpi();
//    g_set_antialiasing(4);
    
    g_init("Voronoi Diagram", WINDOW_SIZE_X, WINDOW_SIZE_Y);
    
    g_def_scale_2D(0,
                   0.0, L, 0.0, L,
                   0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);
    
    sprintf(FileName, "./Voronoi_Diagram_Capture_%d_%d", File_Name, Weight_Flag);
    g_capture_set(FileName);
    
    /* Main loop */
    for (int i_time = 0; i_time < 100000; i_time++) {

        if ((double)i_time * RadiusRate > L * 0.5)
            break;
        
        for (int k=0; k<SiteNumber; k++) {
            
            int counter = CellPixel[k].Pixel_Number;
            
            for (int j=0; j<N; j++) {
                for (int i=0; i<N; i++) {
                    
                    Pixel[i + N * j].x = i * dx;
                    Pixel[i + N * j].y = j * dy;
 
                    if (Pixel[i + N * j].label == -2) {
                        Vector2D tmpPixelVector = {Pixel[i + N * j].x, Pixel[i + N * j].y};
                        
                        if (DistanceFunction(Site[k], tmpPixelVector, DistanceFunctionMode)
                            < (double)i_time * RadiusRate * Weight[k]) {

                            int label_flag = 0;
                            for (int l=0; l<SiteNumber; l++) {
                                if (k != l) {
                                    if (DistanceFunction(Site[k], tmpPixelVector,
                                                         DistanceFunctionMode) / Weight[k]
                                        - DistanceFunction(Site[l], tmpPixelVector,
                                                           DistanceFunctionMode) / Weight[l]
                                        >= EPS) {
                                        label_flag = 1;
                                    }
                                }
                            }
                            if (label_flag == 0) {
                                Pixel[i + N * j].label = k;
                                CellPixel[k].Pixel_Position[counter].x = i;
                                CellPixel[k].Pixel_Position[counter++].y = j;
                            }
                        }
                        
                    }
                } /* for: i, N */
            } /* for: j, N */
            CellPixel[k].Pixel_Number = counter;
        } /* for: SiteNumber */
    
        /* G.L.S.C. 3D */
        g_cls();
        g_scr_color(1.0, 1.0, 1.0);
        g_sel_scale(0);
        
        for (int k=0; k<SiteNumber; k++) {
            int Draw_flag = 1;
            for (int i=0; i<DrawCellNumber; i++) {
                if (DrawCellLabel[i] == k) {
                    Draw_flag = 0;
                }
            }
            if (Draw_flag == 1) {
                for (int i=0; i<CellPixel[k].Pixel_Number; i++) {
                    int tmp_i = (int)CellPixel[k].Pixel_Position[i].x;
                    int tmp_j = (int)CellPixel[k].Pixel_Position[i].y;
                    
                    g_area_color(CellColor[Pixel[tmp_i + N * tmp_j].label].r,
                                 CellColor[Pixel[tmp_i + N * tmp_j].label].g,
                                 CellColor[Pixel[tmp_i + N * tmp_j].label].b,
                                 CellColor[Pixel[tmp_i + N * tmp_j].label].a);
                    g_box_2D(Pixel[tmp_i + N * tmp_j].x,
                             Pixel[tmp_i + N * tmp_j].x + dx,
                             Pixel[tmp_i + N * tmp_j].y,
                             Pixel[tmp_i + N * tmp_j].y + dy,
                             G_NO, G_YES);
                }
            }
        }
        
        /* Sites */
        for (int i=0; i<SiteNumber; i++) {
            g_area_color(0, 0, 0, 1);
            g_circle_2D(Site[i].x, Site[i].y, SiteSize, G_NO, G_YES);
            
            /* Site number */
            g_text_size(12.0);
            g_text_2D_virtual(Site[i].x, Site[i].y, "%d", i);
        }
        
        g_finish();
        
//        g_capture();
    }
    
    /* We draw edges of Voronoi regions. */
    for (int k=0; k<SiteNumber; k++) {
        int Draw_flag = 1;
        for (int i=0; i<DrawCellNumber; i++) {
            if (DrawCellLabel[i] == k) {
                Draw_flag = 0;
            }
        }
        if (Draw_flag == 1) {
            for (int i=0; i<CellPixel[k].Pixel_Number; i++) {
                int tmp_i = (int)CellPixel[k].Pixel_Position[i].x;
                int tmp_j = (int)CellPixel[k].Pixel_Position[i].y;
                
                if (tmp_i != 0 && tmp_j != 0 && tmp_i != N-1 && tmp_j != N-1) {
                    if (Pixel[tmp_i + N * (tmp_j+1)].label != k) {
                        if (Pixel[tmp_i + N * (tmp_j+1)].edgelabel != -1)
                            Pixel[tmp_i + N * tmp_j].edgelabel = -1;
                    }
                    if (Pixel[tmp_i + N * (tmp_j-1)].label != k) {
                        if (Pixel[tmp_i + N * (tmp_j-1)].edgelabel != -1)
                            Pixel[tmp_i + N * tmp_j].edgelabel = -1;
                    }
                    if (Pixel[tmp_i - 1 + N * tmp_j].label != k) {
                        if (Pixel[tmp_i - 1 + N * tmp_j].edgelabel != -1)
                            Pixel[tmp_i + N * tmp_j].edgelabel = -1;
                    }
                    if (Pixel[tmp_i + 1 + N * tmp_j].label != k) {
                        if (Pixel[tmp_i + 1 + N * tmp_j].edgelabel != -1)
                            Pixel[tmp_i + N * tmp_j].edgelabel = -1;
                    }
                }
            }
        }
    }
    /* If all edgelabels for pixels surrounding a pixel are -1,  */
    /* edgelabel of its pixel is -1.  */
//    for (int j=1; j<N-1; j++) {
//        for (int i=1; i<N-1; i++) {
//            if (Pixel[i + N * (j+1)].edgelabel == -1 &&
//                Pixel[i + N * (j-1)].edgelabel == -1 &&
//                Pixel[i+1 + N * j].edgelabel == -1 &&
//                Pixel[i-1 + N * j].edgelabel == -1) {
//                Pixel[i + N * j].edgelabel = -1;
//            }
//        }
//    }
    
    /* We draw edges of Voronoi regions with edges (1-pixel) */
    for (int i_time=0; i_time<1; i_time++) {
        g_cls();
        g_scr_color(1.0, 1.0, 1.0);
        g_sel_scale(0);
        
        for (int k=0; k<SiteNumber; k++) {
            int Draw_flag = 1;
            for (int i=0; i<DrawCellNumber; i++) {
                if (DrawCellLabel[i] == k) {
                    Draw_flag = 0;
                }
            }
            if (Draw_flag == 1) {
                for (int i=0; i<CellPixel[k].Pixel_Number; i++) {
                    int tmp_i = (int)CellPixel[k].Pixel_Position[i].x;
                    int tmp_j = (int)CellPixel[k].Pixel_Position[i].y;
                    
                    g_area_color(CellColor[Pixel[tmp_i + N * tmp_j].label].r,
                                 CellColor[Pixel[tmp_i + N * tmp_j].label].g,
                                 CellColor[Pixel[tmp_i + N * tmp_j].label].b,
                                 CellColor[Pixel[tmp_i + N * tmp_j].label].a);
                    g_box_2D(Pixel[tmp_i + N * tmp_j].x,
                             Pixel[tmp_i + N * tmp_j].x + dx,
                             Pixel[tmp_i + N * tmp_j].y,
                             Pixel[tmp_i + N * tmp_j].y + dy,
                             G_NO, G_YES);
                    
                    if (Pixel[tmp_i + N * tmp_j].edgelabel == -1) {
                        g_area_color(0,0,0,1);
                        g_box_2D(Pixel[tmp_i + N * tmp_j].x,
                                 Pixel[tmp_i + N * tmp_j].x + dx,
                                 Pixel[tmp_i + N * tmp_j].y,
                                 Pixel[tmp_i + N * tmp_j].y + dy,
                                 G_NO, G_YES);
                    }
                }
            }
        }
        
        for (int i=0; i<SiteNumber; i++) {
            g_area_color(0, 0, 0, 1);
            g_circle_2D(Site[i].x, Site[i].y, SiteSize, G_NO, G_YES);
            
            g_text_size(12.0);
            g_text_2D_virtual(Site[i].x, Site[i].y, "%d", i);
        }
        
        g_finish();
        
        g_capture();
    }
    
    /* Edge data */
    sprintf(FileName, "./EdgeData_%d_%d.dat", File_Name, Weight_Flag);
    fp=fopen(FileName, "w");
    for (int j=0; j<N; j++) {
        for (int i=0; i<N; i++) {
            if (Pixel[i + N * j].edgelabel == -1)
                fprintf(fp, "%2.15f\n", 0.0);
            else fprintf(fp, "%2.15f\n", 1.0);
        }
    }
    fclose(fp);
    
    double *Experiment_Pixel;
    Experiment_Pixel = (double *)malloc(sizeof(double) * N * N);
    sprintf(FileName, "./Data/images/%s_%d_%d.dat", type, Image_Name, Image_Time);
    fp=fopen(FileName, "r");
    for (int j=0; j<N; j++){
        for (int i=0; i<N; i++){
            fscanf(fp, "%lf\n", &Experiment_Pixel[i + j * N]);
        }
    }
    fclose(fp);
    
    for (int i_time=0; i_time<1; i_time++) {
        g_cls();
        g_scr_color(1.0, 1.0, 1.0);
        g_sel_scale(0);

        for (int j=0; j<N; j++) {
            for (int i=0; i<N; i++) {
                g_area_color(Experiment_Pixel[i + j*N],
                             Experiment_Pixel[i + j*N],
                             Experiment_Pixel[i + j*N],
                             0.5);
                g_box_2D(i,
                         i + dx,
                         j,
                         j + dy,
                         G_NO, G_YES);
            }
        }
        
        for (int k=0; k<SiteNumber; k++) {
            int Draw_flag = 1;
            for (int i=0; i<DrawCellNumber; i++) {
                if (DrawCellLabel[i] == k) {
                    Draw_flag = 0;
                }
            }
            if (Draw_flag == 1) {
                for (int i=0; i<CellPixel[k].Pixel_Number; i++) {
                    int tmp_i = (int)CellPixel[k].Pixel_Position[i].x;
                    int tmp_j = (int)CellPixel[k].Pixel_Position[i].y;
                    
                    if (Pixel[tmp_i + N * tmp_j].edgelabel == -1) {
                        g_area_color(1,0,0,1);
                        g_box_2D(Pixel[tmp_i + N * tmp_j].x,
                                 Pixel[tmp_i + N * tmp_j].x + dx,
                                 Pixel[tmp_i + N * tmp_j].y,
                                 Pixel[tmp_i + N * tmp_j].y + dy,
                                 G_NO, G_YES);
                    } else {
                        g_area_color(0,1,0,0.2);
                        g_box_2D(Pixel[tmp_i + N * tmp_j].x,
                                 Pixel[tmp_i + N * tmp_j].x + dx,
                                 Pixel[tmp_i + N * tmp_j].y,
                                 Pixel[tmp_i + N * tmp_j].y + dy,
                                 G_NO, G_YES);
                    }
                }
            }
        }
        
        for (int i=0; i<SiteNumber; i++) {
            g_area_color(0, 0, 0, 1);
            g_circle_2D(Site[i].x, Site[i].y, SiteSize, G_NO, G_YES);
        }
        
        g_finish();
        
        g_capture();
    }
    
    for (int i_time=0; i_time<1; i_time++) {
        g_cls();
        g_scr_color(1.0, 1.0, 1.0);
        g_sel_scale(0);

        for (int k=0; k<SiteNumber; k++) {
            int Draw_flag = 1;
            for (int i=0; i<DrawCellNumber; i++) {
                if (DrawCellLabel[i] == k) {
                    Draw_flag = 0;
                }
            }
            
            if (Draw_flag == 0) {
                for (int i=0; i<CellPixel[k].Pixel_Number; i++) {
                    int tmp_i = (int)CellPixel[k].Pixel_Position[i].x;
                    int tmp_j = (int)CellPixel[k].Pixel_Position[i].y;
                    
                    g_area_color(0,0,0,1);
                    g_box_2D(Pixel[tmp_i + N * tmp_j].x,
                             Pixel[tmp_i + N * tmp_j].x + dx,
                             Pixel[tmp_i + N * tmp_j].y,
                             Pixel[tmp_i + N * tmp_j].y + dy,
                             G_NO, G_YES);
                }
            }
            
            if (Draw_flag == 1) {
                for (int i=0; i<CellPixel[k].Pixel_Number; i++) {
                    int tmp_i = (int)CellPixel[k].Pixel_Position[i].x;
                    int tmp_j = (int)CellPixel[k].Pixel_Position[i].y;
                    
                    if (Pixel[tmp_i + N * tmp_j].edgelabel == -1) {
                        g_area_color(1,1,1,1);
                        g_box_2D(Pixel[tmp_i + N * tmp_j].x,
                                 Pixel[tmp_i + N * tmp_j].x + dx,
                                 Pixel[tmp_i + N * tmp_j].y,
                                 Pixel[tmp_i + N * tmp_j].y + dy,
                                 G_NO, G_YES);
                    } else {
                        g_area_color(0,0,0,1);
                        g_box_2D(Pixel[tmp_i + N * tmp_j].x,
                                 Pixel[tmp_i + N * tmp_j].x + dx,
                                 Pixel[tmp_i + N * tmp_j].y,
                                 Pixel[tmp_i + N * tmp_j].y + dy,
                                 G_NO, G_YES);
                    }
                }
            }
        }

        g_finish();
        
        g_capture();
    }
    
    for (int i_time=0; i_time<1; i_time++) {
        g_cls();
        g_scr_color(1.0, 1.0, 1.0);
        g_sel_scale(0);

        /* Sites */
        for (int i=0; i<SiteNumber; i++) {
            g_area_color(0, 0, 0, 1);
            g_circle_2D(Site[i].x, Site[i].y, SiteSize, G_NO, G_YES);
            
            /* Site number */
//            g_text_size(12.0);
//            g_text_2D_virtual(Site[i].x, Site[i].y, "%d", i);
        }

        g_finish();
        
        g_capture();
    }
    
    double *Voronoi_Pixel;
    Voronoi_Pixel = (double *)malloc(sizeof(double) * N * N);
    sprintf(FileName, "./EdgeData_%d_%d.dat", File_Name, Weight_Flag);
    fp=fopen(FileName, "r");
    for (int j=0; j<N; j++){
        for (int i=0; i<N; i++){
            fscanf(fp, "%lf\n", &Voronoi_Pixel[i + j * N]);
        }
    }
    fclose(fp);
    
    int EdgeCounter = 0;
    int EquivalentCounter = 0;
    for (int j=0; j<N; j++){
        for (int i=0; i<N; i++){
            if (Voronoi_Pixel[i + j * N] == 0.0) {
                if (Experiment_Pixel[i + j * N] == 0.0) {
                    EquivalentCounter++;
                }
                EdgeCounter++;
            }
        }
    }
    
    printf("Equivalent rate = %2.15f\n", (double)EquivalentCounter / EdgeCounter);
    printf("EquivalentCounter = %d\n", EquivalentCounter);
    printf("EdgeCounter = %d\n", EdgeCounter);
    
    sprintf(FileName, "./EquivalentRate.dat");
    fp=fopen(FileName, "a");
    fprintf(fp, "%s, Image = %d, Weight = %d, SiteNumber = %d, DrawNumber = %d, Equivalent rate = %2.15f\n",
            type, Image_Name, Weight_Flag, SiteNumber, DrawCellNumber, (double)EquivalentCounter / EdgeCounter);
    fclose(fp);
    
    
    /* free */
    free(Pixel);
    free(CellPixel);
    free(Site);
    free(CellColor);
    free(Experiment_Pixel);
    free(Voronoi_Pixel);
    
    return 0;
}
