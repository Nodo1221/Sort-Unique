(gdb) frame 2
#2  0x0000555555555284 in printarr (arr=0x555555559c90, n=20) at sort_unq2.c:8
8               printf("%s\n", arr[i]);
(gdb) frame 3
#3  0x00005555555557a6 in main () at sort_unq2.c:116
116         printarr(no_dupes, used);
(gdb) p used
$5 = 12

