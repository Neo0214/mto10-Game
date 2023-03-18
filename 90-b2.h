#pragma once


void menu1(int row, int col);
void menu2(int row, int col);
void menu3(int row, int col, int target);
void menu4(int row, int col, int target);
void menu5(int row, int col);
void menu6(int row, int col);
void menu7(int row, int col);
void menu8(int row, int col);
void menu9(int row, int col, int target);
void getcrt(int* row, int* col, int* target, char menu);
void init(int a[10][12], int row, int col);
int findmerge(int a[10][12], char getrow, char getcol, int row, int col, int merge[10][12]);
void calc(int a[10][12], int merge[10][12], int getrow, int getcol);
int score(int a[10][12], int merge[10][12], int row, int col, char getrow, char getcol);
int win(int a[10][12], int target);
int lose(int a[10][12], int row, int col);
void end();
void mergeclear(int merge[10][12]);
void disappear(int a[10][12], int row, int col, int rownow, int colnow, int merge[10][12]);
void twinkle(int a[10][12], int rownow, int colnow);
void see_fall(int a[10][12], int row, int col, int rownow, int colnow);
void findtmp(int a[10][12], int tmp[10][12], int row, int col);
void fill(int a[10][12], int tmp[10][12], int row, int col);
void domenu(int row, int col, char menu);