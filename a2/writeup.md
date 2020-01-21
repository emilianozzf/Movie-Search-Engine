To sum up, the given sorting algorithm is mush better than Bubble Sort in terms of time complexity. In order to make my experiment more reasonable, I choose 2\**20, 2\**15, 2\**10 as input array sizes. Here are the details of my experiment.

---------------------
THE GIVEN SORTING ALGORITHM:
---------------------
Large:    [2\**20 = 1048576] elements     [100663295] comparisons
Med:      [2\**15 = 32768] elements       [1753087] comparisons
Small:    [2\**10 = 1024] elements        [24063] comparisons

---------------------
BUBBLE SORT:
---------------------
Large:    [2\**20 = 1048576] elements     [1.0995116 * 10^12] comparisons
Med:      [2\**15 = 32768] elements       [1073741824] comparisons
Small:    [2\**10 = 1024] elements        [1048576] comparisons

The hardest part of this assignment is to understand the given algorithm and to determine input sizes for anlysis.

Suggestion:
If we encounter an unsorted array with its input size a power of 2, we are higly recomended to choose this given algorithm over bubble sort to sort ti.

