# Minimum-Spanning-Tree

Project 2 for my class “CS331 - Design and Analysis of Algorithms” where I had to implement Prim’s algorithm and Kruskal’s algorithm on graphs with n = 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 nodes, and for each n value, there was an number of edges e = .2, .4, .6, .8 , 1.0 * max number of edges possible. Both algorithms would be ran and times for each were taken for time analysis. 

Sample output

kruskal's_results.txt
Results for: kruskal's

n = 10
e = 0.2
4701.300000000000182

e = 0.400000005960464
6913.600000000000364

e = 0.600000023841858
5333.300000000000182

e = 0.800000011920929
5412.300000000000182

e = 1.000000000000000
5886.399999999999636


n = 20
e = 0.200000002980232
24493.900000000001455

e = 0.400000005960464
27575.299999999999272

e = 0.600000023841858
31881.500000000000000

e = 0.800000011920929
34014.900000000001455

e = 1.000000000000000
37609.900000000001455





Prim's_results.txt

Results for: Prim's

n = 10
e = 0.2
3990.099999999999909

e = 0.400000005960464
8019.699999999999818

e = 0.600000023841858
7940.699999999999818

e = 0.800000011920929
6597.600000000000364

e = 1.000000000000000
6676.500000000000000


n = 20
e = 0.200000002980232
29629.700000000000728

e = 0.400000005960464
33935.900000000001455

e = 0.600000023841858
27930.900000000001455

e = 0.800000011920929
27812.400000000001455

e = 1.000000000000000
26508.599999999998545


output_main.txt

START-> n = 10, e = 0.2

    0    1    2    3    4    5    6    7    8    9 
-------------------------------------------------- 
0| 0    inf  inf  inf  4    inf  inf  inf  42   inf  
1| inf  0    inf  inf  inf  inf  inf  inf  inf  inf  
2| inf  inf  0    inf  47   inf  inf  inf  49   inf  
3| inf  inf  inf  0    inf  inf  inf  inf  inf  inf  
4| 4    inf  47   inf  0    27   34   inf  62   inf  
5| inf  inf  inf  inf  27   0    2    inf  inf  inf  
6| inf  inf  inf  inf  34   2    0    85   inf  inf  
7| inf  inf  inf  inf  inf  inf  85   0    inf  inf  
8| 42   inf  49   inf  62   inf  inf  inf  0    inf  
9| inf  inf  inf  inf  inf  inf  inf  inf  inf  0    

TREE
4 0 
5 4 
6 5 
8 0 
2 4 
7 6 
TREE END

TOTAL MIN COST: 207
TREE SIZE: 6
Not a min spanning tree

START-> n = 10, e = 0.4

    0    1    2    3    4    5    6    7    8    9 
-------------------------------------------------- 
0| 0    inf  inf  inf  39   inf  inf  inf  10   78   
1| inf  0    inf  inf  inf  inf  inf  inf  inf  59   
2| inf  inf  0    32   82   inf  inf  inf  60   inf  
3| inf  inf  32   0    inf  90   inf  inf  81   inf  
4| 39   inf  82   inf  0    90   60   8    46   inf  
5| inf  inf  inf  90   90   0    85   inf  inf  7    
6| inf  inf  inf  inf  60   85   0    11   inf  inf  
7| inf  inf  inf  inf  8    inf  11   0    28   inf  
8| 10   inf  60   81   46   inf  inf  28   0    100  
9| 78   59   inf  inf  inf  7    inf  inf  100  0    

TREE
8 0 
7 8 
4 7 
6 7 
2 8 
3 2 
9 0 
5 9 
1 9 
TREE END

TOTAL MIN COST: 293
TREE SIZE: 9

START-> n = 10, e = 0.6

    0    1    2    3    4    5    6    7    8    9 
-------------------------------------------------- 
0| 0    inf  79   inf  62   inf  61   inf  28   55   
1| inf  0    inf  36   inf  inf  inf  37   23   14   
2| 79   inf  0    62   80   inf  inf  84   61   inf  
3| inf  36   62   0    inf  53   8    inf  97   inf  
4| 62   inf  80   inf  0    22   40   42   21   inf  
5| inf  inf  inf  53   22   0    100  inf  93   34   
6| 61   inf  inf  8    40   100  0    2    inf  inf  
7| inf  37   84   inf  42   inf  2    0    78   67   
8| 28   23   61   97   21   93   inf  78   0    29   
9| 55   14   inf  inf  inf  34   inf  67   29   0    

TREE
8 0 
4 8 
5 4 
1 8 
9 1 
3 1 
6 3 
7 6 
2 8 
TREE END

TOTAL MIN COST: 215
TREE SIZE: 9

START-> n = 10, e = 0.8

    0    1    2    3    4    5    6    7    8    9 
-------------------------------------------------- 
0| 0    13   67   inf  76   inf  17   28   52   60   
1| 13   0    23   2    13   inf  32   6    71   24   
2| 67   23   0    23   20   inf  63   42   68   79   
3| inf  2    23   0    inf  34   87   inf  58   36   
4| 76   13   20   inf  0    21   9    41   24   62   
5| inf  inf  inf  34   21   0    77   inf  90   62   
6| 17   32   63   87   9    77   0    85   inf  inf  
7| 28   6    42   inf  41   inf  85   0    55   80   
8| 52   71   68   58   24   90   inf  55   0    53   
9| 60   24   79   36   62   62   inf  80   53   0    

TREE
1 0 
3 1 
7 1 
4 1 
6 4 
2 4 
5 4 
8 4 
9 1 
TREE END

TOTAL MIN COST: 132
TREE SIZE: 9

START-> n = 10, e = 1

    0    1    2    3    4    5    6    7    8    9 
-------------------------------------------------- 
0| 0    21   66   90   40   36   71   38   23   17   
1| 21   0    80   38   57   78   26   54   2    32   
2| 66   80   0    14   15   21   63   15   23   63   
3| 90   38   14   0    94   94   79   36   76   87   
4| 40   57   15   94   0    66   27   82   13   9    
5| 36   78   21   94   66   0    28   13   20   77   
6| 71   26   63   79   27   28   0    67   34   28   
7| 38   54   15   36   82   13   67   0    21   6    
8| 23   2    23   76   13   20   34   21   0    42   
9| 17   32   63   87   9    77   28   6    42   0    

TREE
9 0 
7 9 
4 9 
5 7 
8 4 
1 8 
2 7 
3 2 
6 1 
TREE END

TOTAL MIN COST: 115
TREE SIZE: 9


