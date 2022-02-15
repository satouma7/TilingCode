//
//  drah.h
//  test_program
//
//  Created by masakazu on 2020/08/10.
//  Copyright © 2020 masakazu. All rights reserved.
//

g_cls();
ig = 0;
g_sel_scale(ig);
g_line_color(0, 0, 0, 1);
g_boundary();

//text
{
    int TextOriginX = xleft_std[ig] + xwid_std[ig] + 10;
    int TextOriginY = ytop_std[ig] + 20;
    int TextSize = 20;
    int j = 0;
    g_text_size(18);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "%s",FileNameTable[(int)FileNumber]);
    
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "Time = %15.15f",t);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "NumberOfCell = %d",NumberOfCell);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "NumberOfVertex = %d",NumberOfVertex);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "Param_Length = %15.15f",Param_Length);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "Param_Volume = %15.15f",Param_Volume);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "mu = %15.15f",mu);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "FinalMeanVolume = %15.15f",FinalMeanVolume);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "FinalMeanVolumeRate = %15.15f",FinalMeanVolumeRate);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "TensionRate = %15.15f",TensionRate);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "dt = %15.15f",dt);
    
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "VMI___ = %15.15f",VMI);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "VMI_th = %15.15f",VMI_th);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "IVI___ = %15.15f",IVI);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "IVITh_ = %15.15f",IVITh);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "MER = %15.15f",MER);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "SER = %15.15f",SER);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "MVR = %15.15f",MVR);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "SVR = %15.15f",SVR);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "MER-3*SER = %15.15f",E_Volume_Mean_Le);
    g_text_standard(TextOriginX, TextOriginY + TextSize * (j ++), "MER+3*SER = %15.15f",E_Volume_Mean_Ri);
    
}
//graphic



//細胞を描画
if(1)
{
    {
        for(int i = 0;i < NumberOfCell;i ++)
        {
            Vector2D v[7];
            for(int j = 0;j < 6;j ++)
                v[j] = Vertex[Cell[i].index[j]].r;
            v[6] = v[0];
            //g_area_color(Cell[i].color.r, Cell[i].color.g, Cell[i].color.b, Cell[i].color.a);
            g_line_color(0,0,0, 1);
            g_polygon_2Ds(v, 7, 1, 0);
        }
    }
}
//重心を描画
if(1)
{
    g_text_size(15);
    for(int i = 0;i < NumberOfCell;i ++)
    {
        g_text_2D_virtual(Cell[i].centroid.x + 5, Cell[i].centroid.y + 5, "%3d",i);
    }
    for(int i = 0;i < NumberOfCell;i ++)
    {
        if(Cell[i].EdgeRatioFlag)
        {
            g_area_color(1, 0, 1, 1);
        }
        else
        {
            g_area_color(0, 0, 0, 1);
        }
        g_circle_2D(Cell[i].centroid.x, Cell[i].centroid.y, 2, 0, 1);
    }
}
//体積を表示
if(0)
{
    g_text_size(10);
    g_area_color(0, 0, 1, 1);
    for(int i = 0;i < NumberOfCell;i ++)
    {
        g_text_2D_virtual(Cell[i].centroid.x, Cell[i].centroid.y - 10, "Re:%2.2f",Cell[i].real_volume);
        g_text_2D_virtual(Cell[i].centroid.x, Cell[i].centroid.y - 20, "Id:%2.2f",Cell[i].ideal_volume);
    }
}
//EdgeRatioを表示
if(0)
{
    g_text_size(10);
    g_area_color(1, 0, 1, 1);
    for(int i = 0;i < NumberOfCell;i ++)
    {
        g_text_2D_virtual(Cell[i].centroid.x, Cell[i].centroid.y - 30, "Ra:%2.2f",Cell[i].EdgeRatio);
    }
}
//頂点位置を描画
if(1)
{
    g_text_size(10);
    g_area_color(1, 0, 0, 1);
    for(int i = 0;i < NumberOfVertex;i ++)
    {
        g_text_2D_virtual(Vertex[i].r.x + 5, Vertex[i].r.y+ 5, "%3d",i);
    }
    for(int i = 0;i < NumberOfVertex;i ++)
    {
        if(Vertex[i].Boundaryflag)//上下の境界細胞群
        {
            g_area_color(0, 1, 0, 1);
        }
        else//内側の細胞群
        {
            g_area_color(1, 0, 0, 1);
        }
        g_circle_2D(Vertex[i].r.x, Vertex[i].r.y, 4, 0, 1);
    }
}

//destination
if(0)
{
    g_area_color(0, 0, 1, 1);
    for(int i = 0;i < NumberOfVertex;i ++)
    {
        g_circle_2D(Vertex[i].destination.x, Vertex[i].destination.y, 2, 0, 1);
    }
}
//頂点にかかる力を描画
if(0)
{
    //周長力
    {
        double amp = 100;
        g_line_color(1, 0, 0, 1);
        for(int i = 0;i < NumberOfVertex;i ++)
        {
            double arrow_length = amp * ~Vertex[i].f_length;
            g_arrow_2Ds(Vertex[i].r, Vertex[i].f_length, arrow_length, arrow_length / 4, 2);
        }
    }
    //体積力
    {
        double amp = 100;
        g_line_color(0, 1, 0, 1);
        for(int i = 0;i < NumberOfVertex;i ++)
        {
            double arrow_length = amp * ~Vertex[i].f_volume;
            g_arrow_2Ds(Vertex[i].r, Vertex[i].f_volume, arrow_length, arrow_length / 4, 2);
        }
    }
}

ig = 1;
g_sel_scale(ig);
g_line_color(0, 0, 0, 1);
g_boundary();

//細胞を描画
{
    int i = iMinLength;
    {
        Vector2D v[7];
        double scale = 4.0;
        for(int j = 0;j < 6;j ++)
            v[j] = scale * (Vertex[Cell[i].index[j]].r - Cell[i].centroid);
        v[6] = v[0];
        //        /g_area_color(Cell[i].color.r, Cell[i].color.g, Cell[i].color.b, Cell[i].color.a);
        g_polygon_2Ds(v, 7, 1, 0);
    }
}

ig = 2;
g_sel_scale(ig);
g_line_color(0, 0, 0, 1);
g_boundary();
//細胞の体積率を表示
{
    g_move_2D(xleft[ig], 0);
    g_plot_2D(xright[ig], 0);
    
    //ものさしを描く
    {
        int Imax = 10;
        double dx = 0.2;
        for(int i = 1;i <= Imax;i ++)
        {
            double x = i * dx + 0.2;
            g_move_2D(x, -0.2);
            g_plot_2D(x, +0.2);
            g_text_2D_virtual(x-0.1, 0.3, "%2.2f",x);
        }
    }
    //E_Volume_Meanを描く
    {
        double x = MVR;
        g_line_color(1, 0, 0, 1);
        g_move_2D(x, -0.2);
        g_plot_2D(x, +0.2);
    }
    //E_Volume_Mean_Leを描く
    {
        double x = E_Volume_Mean_Le;
        g_line_color(0, 0, 1, 1);
        g_move_2D(x, -0.2);
        g_plot_2D(x, +0.2);
    }
    //E_Volume_Mean_Riを描く
    {
        double x = E_Volume_Mean_Ri;
        g_line_color(0, 0, 1, 1);
        g_move_2D(x, -0.2);
        g_plot_2D(x, +0.2);
    }
    //FinalMeanVolumeRate - VolThを描く
    {
        double x = FinalMeanVolumeRate - VolTh;
        g_line_color(0, 1, 0, 1);
        g_move_2D(x, -0.2);
        g_plot_2D(x, +0.2);
    }
    //FinalMeanVolumeRate + VolThを描く
    {
        double x = FinalMeanVolumeRate + VolTh;
        g_line_color(0, 1, 0, 1);
        g_move_2D(x, -0.2);
        g_plot_2D(x, +0.2);
    }
}
g_finish();


