# TilingCode
Source codes used in 'Tiling mechanisms of the Drosophila compound eye through geometrical tessellation'. 

In 'Laser ablation tracking' folder, 'ommatidia.m' is a MATLAB script that tracks bristle cell movement upon laser ablation. 
'ommatidia.fig' is a GUIDE file and should be in the same folder as 'ommatidia.m'. 
'lsmread.m' is necessary to import ZEISS lsm file. 

In 'Voronoi code', 'ommatidia_voronoi0_regularpattern.m' is a MATLAB script that draws multiple Voronoi patterns in Figure S4A. 
'main.cpp' is a C++ code for calculation of the accuracy of Voronoi diagram compared with in vivo pattern. 
By exerting 'main.cpp', we can obtain images of discrete Voronoi diagrams for each ommatidia. 
In order to compile our C++ code,the libraries 'VectorStructOperator.h', 'basic.h, libbasic.a', and'GLSC3D' are required. 
These libraries can be downloaded in the website 'http://www3.u-toyama.ac.jp/akiyama/'. 
See 'makefile' for a compile information about 'main.cpp'. 
'Vertex_XX.dat' and 'Weight_XX.dat' are informations of vertices and weights for each experimental data, respectively. 
See Sheet1 in 'Data.xlsx' for the correspondence table of data labels (XX=1,2,3,...) and kinds of experimental data. 
In 'experimental_database.c', data such as the number of vertices is input, respectively.
By using the script 'AllCalc.sh', we can obtain accuracies of all Voronoi diagram data as 'EquivalentRate.dat'.

In 'Vertex code', main.cpp depends on draw.h, init_glsc.h, MacroStructFunction.h.
draw.h is used to draw the calculation result. Init_glsc.h contains variables for drawing calculation results and window information. 
MacroStructFunction.h describes C++ Language macros, structures, functions, etc. used in main.cpp.

main.cpp takes various parameters as input and returns calculation result and visualization result as output. At that time, if you want to change detailed settings related to output, change main.cpp, draw.h, init_glsc.h and MacroStructFunction.h. Compiling main.cpp uses Unix Makefile. Makefile internally refers to Makefile.GENERIC. Makefile refers to the calculation library for performing calculations and the OpenGL library for performing drawing. These calculation libraries can be obtained from the author's homepage (http://www3.u-toyama.ac.jp/akiyama/) or github (https://github.com/GLSC3DProject/GLSC3D). 

main.cpp corresponds to the calculation engine. On the other hand, main_Multi_47.c is used to input many parameters and perform parallel calculation efficiently. The parameters used can be changed from the 204th line to the 259th line of main_Multi_47.c. main_Multi_47.c internally calls the executable file (the name is “test_program”) of main.cpp and gives parameters to main.cpp. These have the same specifications from main_Multi_48.c to main_Multi_55.c.

DoShellBox is a script for automatically compiling and executing main_Multi_47.c and main.cpp. Normally, execute it like "DoShellBox 47".
Progress is a script for monitoring the progress of calculation.
Folder2Pic is a script to extract only a specific image file from the folder containing the calculation result.
RemoveLen is a script to delete (move) only a specific file from the folder containing the calculation result.
Progress, Folder2Pic, and RemoveLen are not used in normal calculations, but they should be used as appropriate.

In the following, only main.cpp, which is the engine of calculation, will be introduced in detail.

From Line19 to Line151, set various parameters used for calculation.
From Line152 to Line511, the position of the vertex of the actual ommatidia is read from the file, and variables and arrays are initialized.
From Line512 to Line729, the vertex positions are updated using the Vertex Dynamics Model.
From Line730, Line741 visualizes the calculation result.
From Line744 to the end, the calculation results are saved.
