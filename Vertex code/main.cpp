#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <VectorStructOperator.h>
#include <basic.h>
#include <glsc3d_3.h>
#include <time.h>
#include <string.h>
#include "MacroStructFunction.h"

#define FileN (128) // 1行の最大文字数(バイト数)
#define MaxCellNum      (40)
#define    MyDef2D(size,name)            Vector2D    *(name);(name) = (Vector2D *) malloc (sizeof(Vector2D) * (size));
//////////////////////////

int main(int argc, char *argv[])
{

    double Param_Length        = 1;//1.0e-1~1.0e-14
    double Param_Volume        = 0.1;//1.0e-1~1.0e-14
    double mu                  = 1.0;
    double FileNumber          = 7.0;
    double VMI_th              = 1.0e-5;//1.0e-12が一番時間がかかる．
    double VolTh               = 0.3;//1.2-VolThから1.2+VolThの範囲であれば計算が続けられる
    double IVITh               = 1.0e-5;//IVIがIVITh以下なら，十分に理想体積は漸近したとみなせる
    double UseCapture          = 0.0;//0:no capure 1:capure every time 2: capture last time 3: no capture last time
    double FinalMeanVolume     = 0;
    double FinalMeanVolumeRate = 1.2;
    double TensionRate = 1.26;
    double Param_Out = 1.0;
    double dt = 1.0e-3;
    
    double VMI = 0;//Vertex Movement Index
    double IVI = 0;//Ideal Volume Index
    double MER = 0;
    double SER = 0;
    double MVR = 0.0;
    double E_Volume_Mean_Le = 0.0;
    double E_Volume_Mean_Ri = 0.0;
    double SVR = 0.0;

    double t = 0;
    double tmax = 100000.0;
    int    StopFlag = 1;
    int    LastCalcTimeFlags = 0;
    int    ExitCode = 0;
    int    iMinLength = 0;

    //Param Over ride
    if(56)
    {
        int FolderNumber = 56;
        if(FolderNumber == 47)
        {
            Param_Length        = 0.012045035402588;//47
            Param_Volume        = 0.000585702081806;//47
            FileNumber          = 1;
			UseCapture          = 1;

        }
        if(FolderNumber == 48)
        {
            Param_Length        = 0.006579332246576;//49
            Param_Volume        = 8.497534359e-6;//49
            FileNumber          = 2;
            UseCapture          = 1;
        }
        if(FolderNumber == 49)
        {
            Param_Length        = 0.004862601580065;//49
            Param_Volume        = 0.001450828778496;//49
            FileNumber          = 3;
			UseCapture          = 1;

        }
        if(FolderNumber == 50)
        {
            Param_Length        = 0.002656087782947;//50
            Param_Volume        = 0.000432876128108;//50
            FileNumber          = 7;
			UseCapture          = 1;

        }
        if(FolderNumber == 51)
        {
            Param_Length        = 0.003593813663805;//51
            Param_Volume        = 0.000585702081806;//51
            FileNumber          = 8;
			UseCapture          = 1;

        }
        if(FolderNumber == 52)
        {
            Param_Length        = 0.004862601580065;//52
            Param_Volume        = 0.001450828778496;//52
            FileNumber          = 9;
			UseCapture          = 1;

        }
        if(FolderNumber == 53)
        {
            Param_Length        = 0.722080901838548;//53
            Param_Volume        = 0.001450828778496;//53
            FileNumber          = 1;
            UseCapture          = 1;
            Param_Out           = 1;
        }
        if(FolderNumber == 54)
        {
            Param_Length        = 0.722080901838548;//54
            Param_Volume        = 0.00107226722201;//54
            FileNumber          = 2;
            UseCapture          = 1;
            Param_Out           = 1;
        }
        if(FolderNumber == 55)
        {
            Param_Length        = 0.722080901838548;//55
            Param_Volume        = 0.001450828778496;//55
            FileNumber          = 3;
            UseCapture          = 1;
            Param_Out           = 1;
        }
		if(FolderNumber == 56)
		{
			double Param_Length_50        = 0.002656087782947;//50
            double Param_Volume_50        = 0.000432876128108;//50
            double Param_Length_51        = 0.003593813663805;//51
            double Param_Volume_51        = 0.000585702081806;//51
            double Param_Length_52        = 0.004862601580065;//52
            double Param_Volume_52        = 0.001450828778496;//52
            
            VMI_th = 1.0e-6;

//            Param_Length        = pow(Param_Length_50*Param_Length_51*Param_Length_52,1./3);//SouJouHeikin
//            Param_Volume        = pow(Param_Volume_50*Param_Volume_51*Param_Volume_52,1./3);//SouJouHeikin
			Param_Length        = (Param_Length_50+Param_Length_51+Param_Length_52)/3;//SoukaHeikin
			Param_Volume        = (Param_Volume_50+Param_Volume_51+Param_Volume_52)/3;//SoukaHeikin
//            Param_Length        = Param_Length_50;//50
//            Param_Volume        = Param_Volume_50;//50
//            Param_Length        = Param_Length_51;//51
//            Param_Volume        = Param_Volume_51;//51
//            Param_Length        = Param_Length_52;//52
//            Param_Volume        = Param_Volume_52;//52
			FileNumber          = 10;
			UseCapture          = 1;
//            FinalMeanVolumeRate = 1;
			Param_Out           = 0;
		}

    }
    double dummy;
    GetParam2(argc, argv, 100,
          &(Param_Length),                //p0
          &(Param_Volume),                //p1
          &(mu),                          //p2
          &(UseCapture),                  //p3
          &(FileNumber),                  //p4
          &(VMI_th),                      //p5
          &(VolTh),                       //p6
          &(FinalMeanVolumeRate),         //p7
          &(TensionRate),                 //p8
          &(Param_Out),                   //p9
          &(dt),                          //p10
          &(dummy),
          NULL
          );

    //Make Folder Name
    char filename[256];

    sprintf(filename, "");
    sprintf(filename, "%s%s_%15.15f_",filename,"Len",Param_Length);
    sprintf(filename, "%s%s_%15.15f_",filename,"Vol",Param_Volume);
    sprintf(filename, "%s%s_%15.15f_",filename,"mu",mu);
    sprintf(filename, "%s%s_%d_",filename,"FileNumber",(int)FileNumber);
    sprintf(filename, "%s%s_%15.15f_",filename,"VMI_th",VMI_th);
    sprintf(filename, "%s%s_%15.15f_",filename,"VolTh",VolTh);
    sprintf(filename, "%s%s_%15.15f_",filename,"Outforce",Param_Out);

    char FileNameTable[100][1024] =
    {
        "dummy",
        "01_ctrl28hr_6.csv",
        "02_ctrl28hr_23.csv",
        "03_ctrl28hr_24(ctrl0).csv",
        "04_ctrl42hr_11(ctrl1).csv",
        "05_ctrl42hr_12.csv",
        "06_ctrl42hr_24.csv",
        "07_upd28hr_9.csv",
        "08_upd28hr_17.csv",
        "09_upd28hr_26(upd0).csv",
        "10_upd42hr_12.csv",
        "11_upd42hr_27(upd1).csv",
        "12_upd42hr_28.csv"
    };

    //Input File
    FILE *fp;
#ifdef __APPLE__
    char LocalFileName[1024]="/Users/masakazu/Dropbox/SatohProjects/2DVertex/Data/";
#endif
#ifdef __linux__
    printf("Linux\n");
    char LocalFileName[1024]="/home/masakazu/Dropbox/SatohProjects/2DVertex/Data/";
#endif
    
    sprintf(LocalFileName, "%s%s",LocalFileName,FileNameTable[(int)FileNumber]);
    fp = fopen(LocalFileName,"r");
    if (fp == NULL) {
        printf("ファイルが開けませんでした\n");
        exit (1);
    }
    else
    {
        printf("ファイルのオープンに成功しました\n");
    }
    //行数の判定
    int MaxGyosu = 0;
    {
        char *buf;
        buf = (char *) malloc(sizeof(char) * FileN);
        while( NULL != fgets( buf, FileN, fp ) ) MaxGyosu++;
        //printf("MaxGyosu = %d\n",MaxGyosu);
    }
    int NumberOfVertex = MaxGyosu - 1;//NumberOfVertexは頂点の個数
    Vertex = (VertexStruct *)malloc(sizeof(VertexStruct ) *  NumberOfVertex);
    VertexOld = (VertexStruct *)malloc(sizeof(VertexStruct ) *  NumberOfVertex);
    //int CVTable[MaxCellNum][7];
//    int *CVTable;
//    CVTable = (int *) malloc(sizeof(int) * MaxCellNum * 7);
//#define CVTable(i,j)        CVTable[MaxCellNum * (i) + (j)]
    
    int NumberOfCell = 0;
    //NumberOfCellの判定
    {
        int retu[10];
        char *buf;
        buf = (char *) malloc(sizeof(char) * FileN);
        for(int i = 0;i < FileN;i ++) buf[i] = '\0';

        
        for(int i = 0;i < 10;i ++)
        {
            retu[i] = -1;
        }

        fseek( fp, 0L, SEEK_SET );
        fgets( buf, FileN, fp );
        for(int i = 0;i < MaxGyosu;i ++)
        {
            fgets( buf, FileN, fp );
            sscanf(buf,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",&retu[0],&retu[1],&retu[2],&retu[3],&retu[4],&retu[5],&retu[6],&retu[7],&retu[8],&retu[9]);
    
            if(retu[3] != 0)
            {
                NumberOfCell = retu[3];
                if(NumberOfCell > MaxCellNum)
                {
                    printf("NumberOfCell = %d exceed MaxCellNum = %d!!\n",NumberOfCell, MaxCellNum);
                    return 0;
                }
            }
        }
        //printf("NumberOfCell = %d\n",NumberOfCell);
    }
    Cell = (CellStruct *)malloc(sizeof(CellStruct) * NumberOfCell);
    CellInit = (CellStruct *)malloc(sizeof(CellStruct) * NumberOfCell);
    //読み込み
    {
        int retu[10];
        char *buf;
        buf = (char *) malloc(sizeof(buf) * FileN);
        for(int i = 0;i < FileN;i ++) buf[i] = '\0';

        for(int i = 0;i < 10;i ++)
        {
            retu[i] = -1;
        }

        fseek( fp, 0L, SEEK_SET );
        fgets( buf, FileN, fp );
        //sscanf(buf,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",&retu[0],&retu[1],&retu[2],&retu[3],&retu[4],&retu[5],&retu[6],&retu[7],&retu[8],&retu[9]);
        //printf("%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d\n",retu[0],retu[1],retu[2],retu[3],retu[4],retu[5],retu[6],retu[7],retu[8],retu[9]);
        for(int i = 0;i < MaxGyosu;i ++)
        {
            fgets( buf, FileN, fp );
            //printf("%s",buf);
            sscanf(buf,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",&retu[0],&retu[1],&retu[2],&retu[3],&retu[4],&retu[5],&retu[6],&retu[7],&retu[8],&retu[9]);
            //printf("%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d,%4d\n",retu[0],retu[1],retu[2],retu[3],retu[4],retu[5],retu[6],retu[7],retu[8],retu[9]);
            Vertex[i].r.x = retu[1];
            Vertex[i].r.y = 500 - retu[2];
            if(retu[3] != 0)
            {
                NumberOfCell = retu[3];
                Cell[NumberOfCell - 1].index[0] = retu[4] - 1;
                Cell[NumberOfCell - 1].index[1] = retu[5] - 1;
                Cell[NumberOfCell - 1].index[2] = retu[6] - 1;
                Cell[NumberOfCell - 1].index[3] = retu[7] - 1;
                Cell[NumberOfCell - 1].index[4] = retu[8] - 1;
                Cell[NumberOfCell - 1].index[5] = retu[9] - 1;
            }
        }
    }
    fclose(fp);
    //乱数を初期化
    //unsigned long seed = time(NULL);
    unsigned long seed = FileNumber;
    init_genrand64(seed);

    //Vertexのその他を初期化
    for(int i = 0;i < NumberOfVertex;i ++)
    {
        Vertex[i].flag = 0;
        Vertex[i].f_length = Zero2D;
        Vertex[i].f_out = Zero2D;
        Vertex[i].f_random = Zero2D;
        Vertex[i].f_volume = Zero2D;
        
        Vertex[i].Boundaryflag = -1;
        Vertex[i].destination = Zero2D;
    }

    //組織を真ん中に平行移動
    {
        Vector2D g = Zero2D;
        for(int i = 0;i < NumberOfVertex;i ++)
        {
            g += Vertex[i].r;
        }
        g /= NumberOfVertex;
        
        for(int i = 0;i < NumberOfVertex;i ++)
        {
            Vertex[i].r -= g;
        }
    }
    //Boundaryflagを設定
    {
        double yTopBottomList[][2] = {
            {YLEN / 4,-YLEN / 4},//Dummy
            {YLEN / 4,-YLEN / 4},//Case FileNumber = 1
            {YLEN / 4 - YLEN / 20,-YLEN / 4 + YLEN / 20},//Case FileNumber = 2
            {YLEN / 4,-YLEN / 4 + YLEN / 40},//Case FileNumber = 3
            {YLEN / 4,-YLEN / 4},//Case FileNumber = 4
            {YLEN / 4,-YLEN / 4},//Case FileNumber = 5
            {YLEN / 4,-YLEN / 4},//Case FileNumber = 6
            {YLEN / 4 - YLEN / 20,-YLEN / 4 + YLEN / 20},//Case FileNumber = 7
            {YLEN / 4,-YLEN / 4},//Case FileNumber = 8
            {YLEN / 4 + YLEN / 20,-YLEN / 4 - YLEN / 20},//Case FileNumber = 9
            {YLEN / 4 - YLEN / 19,-YLEN / 4 + YLEN / 20},//Case FileNumber = 10
            {YLEN / 4 + YLEN / 200,-YLEN / 4},//Case FileNumber = 11
            {YLEN / 4 - YLEN / 40,-YLEN / 4 + YLEN / 20},//Case FileNumber = 12
            {YLEN / 4,-YLEN / 4}//Dummy
        };
        double yTop = yTopBottomList[(int)FileNumber][0];
        double yBottom = yTopBottomList[(int)FileNumber][1];
        for(int i = 0;i < NumberOfVertex;i ++)
        {
            if(Vertex[i].r.y > yTop || Vertex[i].r.y < yBottom)
            {
                Vertex[i].Boundaryflag = 1;
            }
            else
            {
                Vertex[i].Boundaryflag = 0;
            }
        }
    }
    
    //destinationを設定
    {
        for(int i = 0;i < NumberOfVertex;i ++)
        {
            Vertex[i].destination = Vertex[i].r;
            if(Vertex[i].Boundaryflag)
            {
                Vertex[i].destination.y *= TensionRate;
            }
        }
    }
    //Cellの各種値を設定
    for(int i = 0;i < NumberOfCell;i ++)
    {
        Cell[i].index_num = 6;
        //現時点の細胞の体積を計算
        Vector2D v[8];
        for(int j = 0; j < 6;j ++)
            v[j + 1] = Vertex[Cell[i].index[j]].r;
        v[0] = v[6];
        v[7] = v[1];
        Vector3D T = Zero3D;
        for(int j = 1; j <= 6;j ++)
            T += R2_to_R3(v[j]) ^ R2_to_R3(v[j + 1]);
        double S = 0.5 * ~T;
        Cell[i].real_volume = S;
        Cell[i].ideal_volume = Cell[i].real_volume;

        //細胞の色を決める
        Cell[i].color.r = genrand64_real2();
        Cell[i].color.g = genrand64_real2();
        Cell[i].color.b = genrand64_real2();
        Cell[i].color.a = 1;
        
        //EdgeRatioFlag
        Cell[i].EdgeRatioFlag = 1;

    }
    //Calc FinalMeanVolume
    {
        FinalMeanVolume = 0;
        for(int i = 0;i < NumberOfCell;i ++)
        {
            //printf("Cell[%03d].real_volume = %f\n",i,Cell[i].real_volume);
            FinalMeanVolume += Cell[i].real_volume;
        }
        FinalMeanVolume /= NumberOfCell;
    }
    FinalMeanVolume *= FinalMeanVolumeRate;

    //EdgeRatioFlagを計算する．
    {
        if(Param_Out > 1.0e-10)
        {
            for(int i = 0;i < NumberOfCell;i ++)
            {
                int tmp = 0;
                for(int j = 0; j < 6;j ++)
                {
                    tmp += Vertex[Cell[i].index[j]].Boundaryflag;
                }
                if(tmp == 0)
                {
                    Cell[i].EdgeRatioFlag = 1;
                }
                else
                {
                    Cell[i].EdgeRatioFlag = 0;
                }
            }
        }
    }
    /******************************** glsc variables ***********************************/
    double          xleft_std[IG], ytop_std[IG];
    double          xwid_std[IG], ywid_std[IG];
    double          xleft[IG], xright[IG];
    double          ybottom[IG], ytop[IG];
    double          znear[IG],zfar[IG];
    double          direction_x[IG],direction_y[IG],direction_z[IG];
    double          EYE_r[IG];
    double          normal_x[IG],normal_y[IG],normal_z[IG];
    double          red, green, blue;

    int             ig;
    /******************************** glsc variables ***********************************/

//#include "init_glsc.h"
    if(((int)UseCapture == 0) || ( (int)UseCapture == 1))
    {
#include "init_glsc.h"
    }

    //Judge Center Cell
    {
        for(int i = 0;i < NumberOfCell;i ++)
        {
            Vector2D v[8];
            for(int j = 0; j < 6;j ++)
            v[j + 1] = Vertex[Cell[i].index[j]].r;
            v[0] = v[6];
            v[7] = v[1];

            //細胞の重心を計算
            Vector2D centroid = Zero2D;
            for(int j = 1; j <= 6;j ++)
            {
                centroid += v[j];
            }
            Cell[i].centroid = centroid / 6;
        }
        Vector2D g = Zero2D;
        for(int i = 0;i < NumberOfCell;i ++)
        {
            g += Cell[i].centroid;
        }
        g /= NumberOfCell;

        MyDef(NumberOfCell, CellCenterLen);
        for(int i = 0;i < NumberOfCell;i ++)
        {
            CellCenterLen[i] = ~(Cell[i].centroid - g);
        }

        double MinLength = CellCenterLen[iMinLength];

        for(int i = 1;i < NumberOfCell; i++)
        {
            if(CellCenterLen[i] < MinLength)
            {
                MinLength = CellCenterLen[i];
                iMinLength = i;
            }
        }

        //printf("iMinLength = %d\n",iMinLength);
    }
    //Cellの初期状態を保存
    for(int i = 0;i < NumberOfCell;i ++)
    {
        CellInit[i] = Cell[i];
    }
    ////////////////////////////////// Time Loop ///////////////////////////////////
    for(int i_time = 0; StopFlag; i_time ++)
    {
        t = i_time * dt;

        /*理想体積がどれほど，FinalMeanVolumeに近づいたかを計算する*/
        {
            //IVIは，初期は大きな値を取るかもしれないが，時間が十分たてば0に近くなる．
            IVI = 0;
            for(int i = 0;i < NumberOfCell;i ++)
            {
                IVI += FinalMeanVolume / Cell[i].ideal_volume - 1;
            }
            IVI /= NumberOfCell;
        }
        /*Calc Vertex Movement Index*/
        if(i_time > 0 )
        {
            double zure;
            double zure_m = 0;
            for(int i = 0;i < NumberOfVertex;i ++)
            {
                zure_m = ~(Vertex[i].r - VertexOld[i].r) / dt;
            }
            zure_m /= NumberOfVertex;
            VMI = zure_m;
            
        }
        /*Calc Volume Mean SD*/
        {
            MVR = 0;
            for(int i = 0;i < NumberOfCell;i ++)
            {
                MVR += Cell[i].real_volume / CellInit[i].real_volume;
            }
            MVR /= NumberOfCell;
            
            SVR = 0;
            for(int i = 0;i < NumberOfCell;i ++)
            {
                SVR += SQ(Cell[i].real_volume / CellInit[i].real_volume - MVR);
            }
            SVR /= NumberOfCell;
            SVR = sqrt(SVR);
            
            /*E_Volume_Mean_Leは体積分布のすごい左端の値*/
            /*E_Volume_Mean_Riは体積分布のすごい右端の値*/
            E_Volume_Mean_Le = MVR - 3 * SVR;
            E_Volume_Mean_Ri = MVR + 3 * SVR;
            
        }
        
        if(t < tmax)
        {
            if(
                 (E_Volume_Mean_Le < FinalMeanVolumeRate - VolTh) ||
                 (FinalMeanVolumeRate + VolTh < E_Volume_Mean_Ri)
               )
                
            {
                /*細胞の初期体積との比率がある範囲に入っている場合は計算を続行．そうでない場合終了*/
                StopFlag = 0;
                LastCalcTimeFlags = 1;
                ExitCode = 1;
            }
            if((i_time > 0) && (VMI < VMI_th)//ステップが１より大きく，VMIがある程度小さい時
               && (IVI < IVITh))//全ての細胞のIdeal volumeが十分に漸近したとき
            {
                StopFlag = 0;
                LastCalcTimeFlags = 1;
                ExitCode = 2;
            }
        }
        else
        {
            /*計算時間がtmaxを超えたら問答無用で落とす*/
            StopFlag = 0;
            //LastCalcTimeFlags = 1;

            ExitCode = 3;
        }

        if(1)
        {
            //double T_mean = 0;
            for(int i = 0;i < NumberOfCell;i ++)
            {
                Vector2D v[8];
                for(int j = 0; j < 6;j ++)
                    v[j + 1] = Vertex[Cell[i].index[j]].r;
                v[0] = v[6];
                v[7] = v[1];

                //細胞の重心を計算
                Vector2D centroid = Zero2D;
                for(int j = 1; j <= 6;j ++)
                {
                    centroid += v[j];
                }
                Cell[i].centroid = centroid / 6;
                //現時点の細胞の体積を計算
                Vector3D T = Zero3D;
                for(int j = 1; j <= 6;j ++)
                    T += R2_to_R3(v[j]) ^ R2_to_R3(v[j + 1]);
                double S = 0.5 * ~T;
                Cell[i].real_volume = S;
                //IdealVolumeの計算
                Cell[i].ideal_volume += mu * dt * (FinalMeanVolume - Cell[i].ideal_volume);

                //周長力の計算
                for(int j = 1; j <= 6;j ++)
                {
                    Vector2D tmp,hoge;
                    tmp = v[j] - v[j - 1];
                    hoge = v[j] - v[j + 1];
                    tmp = tmp / (~tmp);
                    hoge = hoge / (~hoge);
                    Vertex[Cell[i].index[j - 1]].f_length -= tmp + hoge;
                }
                //体積力の計算
                for(int j = 1; j <= 6;j ++)
                {
                    Vector3D del_S;
                    T = (R2_to_R3(v[j+1]) - R2_to_R3(v[j]))^(R2_to_R3(v[j-1]) - R2_to_R3(v[j]));
                    //del_S = T ^ (R2_to_R3(v[j + 1]) - R2_to_R3(v[j - 1])) * ~T / 2.0;
//                    T_mean += ~T;
                    del_S = T ^ (R2_to_R3(v[j + 1]) - R2_to_R3(v[j - 1])) / (2.0 * ~T);
                    Vertex[Cell[i].index[j - 1]].f_volume += (Cell[i].real_volume - Cell[i].ideal_volume) * R3_to_R2(del_S);
                    //T_mean += ~del_S;
                }
            }

//            T_mean /= (6 * NumberOfCell);
//            printf("T_mean = %f\n",T_mean);
            //Calc Outer Force
            for(int i = 0;i < NumberOfVertex;i ++)
            {
                Vertex[i].f_out = Param_Out * Vertex[i].Boundaryflag*(Vertex[i].destination - Vertex[i].r);
            }
            /*Calc All Force*/
            for(int i = 0;i < NumberOfVertex;i ++)
            {
                Vertex[i].f_length = Param_Length * Vertex[i].f_length;
                Vertex[i].f_volume = Param_Volume * Vertex[i].f_volume;
            }
            for(int i = 0;i < NumberOfVertex;i ++)
            {
                Vertex[i].f =
                Vertex[i].f_length
                + Vertex[i].f_volume
                + Vertex[i].f_out;
            }

            /*update VertexOld*/
            for(int i = 0;i < NumberOfVertex;i ++)
            {
                VertexOld[i]= Vertex[i];
            }
            
            /*Calc Position*/
            for(int i = 0;i < NumberOfVertex;i ++)
            {
                Vertex[i].r += dt * Vertex[i].f;
            }

            //Calc Cell Shape
            {
                for(int i = 0;i < NumberOfCell;i ++)
                {
                    Vector2D v[8];
                    for(int j = 0; j < 6;j ++)
                    v[j + 1] = Vertex[Cell[i].index[j]].r;
                    v[0] = v[6];
                    v[7] = v[1];

                    double EdgeLength[6];
                    for(int j = 1; j <= 6;j ++)
                    {
                        EdgeLength[j - 1] = ~(v[j + 1] - v[j]);
                    }
                    double MaxEdgeLength;
                    double MinEdgeLength;
                    MxmnCheck(6, EdgeLength, &MaxEdgeLength, &MinEdgeLength);
                    
                    Cell[i].EdgeRatio = -1;
                    if(Cell[i].EdgeRatioFlag)
                    {
                        Cell[i].EdgeRatio = MinEdgeLength / MaxEdgeLength;
                    }
                }

                MER = 0;
                int counter = 0;
                for(int i = 0;i < NumberOfCell;i ++)
                {
                    if(Cell[i].EdgeRatio > 0)
                    {
                        MER += Cell[i].EdgeRatio;
                        counter++;
                    }
                }
                MER /= counter;

                SER = 0;
                counter = 0;
                for(int i = 0;i < NumberOfCell;i ++)
                {
                    if(Cell[i].EdgeRatio > 0)
                    {
                        SER += SQ(Cell[i].EdgeRatio - MER);
                        counter++;
                    }
                }
                SER /= counter;
                SER = sqrt(SER);
            }

        }
        if (
            (
             ((int)UseCapture == 0) ||
             ((int)UseCapture == 1)
            )   &&
            (i_time % ((int)INTV) == 0)
            )
        {
#include "draw.h"
            if((int)UseCapture == 1)
                g_capture();
        }
    }

    if(LastCalcTimeFlags)
    {
        if (
            ((int)UseCapture == 2)
            )
        {
#include "init_glsc.h"
#include "draw.h"
        g_capture();
        }
        //Output File
        FILE *fp2;
        fp2 = fopen("data.txt","a");
        fprintf(fp2, "%15.15f %15.15f %15.15f %15.15f %15.15f %15.15f %15.15f %15.15f %15.15f %15.15f %15.15f %15.15f %15.15f %15.15f %15.15f\n",
                Param_Length,           //01
                Param_Volume,           //02
                mu,                     //03
                FileNumber,             //04
                VMI_th,                 //05
                FinalMeanVolume,        //06
                MER,                    //07
                SER,                    //08
                t,                      //09
                VolTh,                  //10
                MVR,                    //11
                SVR,                    //12
                VMI,                    //13
                IVI,                    //14
                (double)ExitCode        //15
                );
        fclose(fp2);

    }
    //fclose(fp);
    
    free(Vertex);
    free(Cell);
    free(CellInit);
    return 0;
}
