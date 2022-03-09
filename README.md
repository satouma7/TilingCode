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

Details of 'Vertex code' will be added soon. 
