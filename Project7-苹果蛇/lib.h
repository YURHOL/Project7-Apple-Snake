#include <stdio.h>
#include <Windows.h>
#include <io.h>

#pragma warning(disable : 4996)

/**
 * 更改文字颜色
 */
void color(int c) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);//更改文字颜色
}

/**
 * 光标移动到(x,y)位置
 */
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);//使光标到这个（x，y）的位置，需要调用#include<windows.h>
}

/**
 * 隐藏控制台光标
 */
void HideCursor() {
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

/**
 * 设置控制台的宽高
 */
void setcmdHW(int width, int height) {
    char chCmd[32];
    sprintf(chCmd, "mode con cols=%d lines=%d", width, height);
    system(chCmd);
}

/**
 * 清空控制台
 */
void cls() {
    system("cls");
}

/**
 * 暂停，按任意键继续
 */
void pause() {
    system("pause");
}

/**
 * 获取指定目录下的所有文件名
 * 参数：字符串数组，搜索路径，文件后缀名，最大数量
 * 返回值：-1=未找到，0=正常
 */
int getFilesName(char* arr[], char* path, char* suffix, int count) {
    char pathstr[MAX_PATH];
    sprintf(pathstr, "%s/*.%s", path, suffix);

    struct _finddata_t fa;
    int fHandle = _findfirst(pathstr, &fa);
    if (fHandle == -1) {
        return -1;//异常返回：当前目录下没有文件
    }
    int i = 0;
    do {
        arr[i] = (char*)malloc(MAX_PATH);
        if (arr[i]) {
            strcpy(arr[i], fa.name);
        }
        i++;
        //printf("调试输出：找到文件:%s\n", fa.name);
    } while ((_findnext(fHandle, &fa) == 0) && (i < count));
    _findclose(fHandle);
    return 0;
}

/**
 * 获取指定目录下，指定类型文件的数量
 * 参数：搜索路径，文件后缀名
 * 返回值：指定类型文件的数量
 */
int getFilesNum(char* path, char* suffix) {
    char pathstr[MAX_PATH];
    sprintf(pathstr, "%s/*.%s", path, suffix);

    struct _finddata_t fa;
    int fHandle = _findfirst(pathstr, &fa);
    if (fHandle == -1) {
        return 0;
    }
    int i = 0;
    do {
        i++;
    } while ((_findnext(fHandle, &fa) == 0));
    _findclose(fHandle);

    return i;
}

//简化名称：sas
#define sas(a, b) StrAndStr(a, b)
/**
 * 拼接字符串（加强版）
 * 参数：字符串a，字符串b（可以为常量）
 * 返回值：字符串指针，0为异常
 */
char* StrAndStr(char* a, char* b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    if (strlen(a) == 0 || strlen(b) == 0) {
        return 0;
    }
    char* s = (char*)malloc(strlen(a) + strlen(b) + 1);
    if (s) {
        return strcat(strcpy(s, a), b);
    }
}