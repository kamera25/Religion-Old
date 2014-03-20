//グローバル変数の定義
extern int scid1;
extern int hsid1;
extern int litid1;
extern int litid2;
extern int wpitem[10][10][10];
extern int keyin[20];
extern int lddata[100];
extern int modelId[30];
extern int motionId[30];
extern int QId[30];
extern int BoneId[30];
extern int opimg;
extern int grd1;
extern int wal1;
extern int wpmodel[30];
extern int wpbone[30][15];
extern int Iinfo[5][15];
extern int Eneinfo[20][5];
extern int FontID[5];
extern char pat[MAX_PATH];
extern RECT recwindow;
extern HWND hwnd;


//関数の定義


int firstload();
int loadimg();
int opning();
int Eneload();
int OpsRoops();
int grdload(int grdid, int grdkd, int lightkd, int shodowkd);
int kabaddi(int *output1, int *output2, int input1, int input2);
int keyout(int keydev, int stuate);
int gunload(int wpkind, int wpno, int wpmin_sub);
int Lunchergun(int subject, int Moveflg,int Gndflg);
int Posemenu(int *modsc);



//オペレーションモード関数

