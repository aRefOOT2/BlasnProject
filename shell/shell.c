/*

Blasn Kernel Shell version 1.0.7 PA

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define MAX_INPUT 100
#define CURSOR_CHAR '_'


char* user = "root";
char* hostname = "blasnlive";
char* currentdir = "~";
char* prmpt = "#";


void command(const char *cmd)
{
    if (strcmp(cmd, "hello") == 0)
    {
        printf("Hello, user!\n");
    } else if (strcmp(cmd, "exit") == 0)
    {
        printf("Exiting shell...\n");
        exit(0); // プログラムを終了
    } else if (strcmp(cmd, "help") == 0)
    {
        printf("Available commands:\n");
        printf("  hello - Greet the user\n");
        printf("  exit - Exit the shell\n");
        printf("  help - Show this help message\n");
        printf("  version - Show this program information.\n");
    } else if (strcmp(cmd, "exit") == 0)
    {
        return; 
    } else if (strcmp(cmd, "version") == 0)
    {
        printf("Blasn Kernel Shell  Version 1.0.7 Pre Alpha\n");
        printf("Type 'help' to see available in-kernel commands.\n");
    } else
    {
        printf("Unknown command: %s\n", cmd);
    }
}


void cursor(bool print)
{
    if (print)
    {
        printf("\b%c", CURSOR_CHAR); // カーソル表示
    } else {
        printf("\b"); // カーソル消去
    }
}


void clearline(int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("\b \b"); // カーソルを戻して空白を入れて消去
    }
}


int main()
{
  char input[MAX_INPUT];
  int timer = 0;
  bool show = true;
  
  
  printf("Welcome to the Blasn kernel shell! Type 'version' print this program information, Type 'help' for commands.\n");

  for (int loop1 = 0; loop1 < 2; loop1++)
  {

    // プロンプトの設定
   prmpt = (strcmp(user, "root") == 0) ? "#" : "$";

   char user_home_directory[50];
   snprintf(user_home_directory, sizeof(user_home_directory), "/home/%s", user);

   if (strcmp(currentdir, "/root") == 0) // currentdir が "/root" の場合
    {
        
     currentdir = "^"; // カレントディレクトリが "/root" の場合
    } else if (strncmp(currentdir, "/home/", 6) == 0 && strcmp(currentdir, user_home_directory) == 0) // "/home/[ユーザー名]" の場合
    {
     currentdir = "~"; // ユーザーのホームディレクトリにいる場合
    }      

  printf("%s@%s %s %s ",user, hostname, currentdir, prmpt); // プロンプトを表示
      
  memset(input, 0, sizeof(input)); // 入力バッファをクリア
  int pos = 0; // 入力位置
  
  for (int loop2 = 0; loop2 < 2; loop2++)
  {
    timer = 1 + (timer % 5);
     
     // カーソル点滅の処理
    if (timer % 5 == 0)
     {
     cursor(show);
     show != show;
     }

    char ch = getchar(); // 1文字ずつ入力を取得
    if (ch == EOF) // 入力が終わった場合は無視
     {
      continue;
     }
    if (ch == '\n') // 改行が入力された場合
     {
      loop1--;
      if (pos > 0)
      {
       input[pos] = '\0'; // 文字列の終端を設定
       clearline(pos);
       command(input);
      }
     break; // 入力ループを抜ける
     } else if (ch == 127 || ch == '\b') // Backspaceが押された場合
      {
       if (pos > 0)
           {
           pos--; // 入力位置を1つ戻す
           printf("\b \b"); // カーソルを消して文字を消去
           fflush(stdout); // 出力をフラッシュ
           }
         }else if (pos < MAX_INPUT - 1) // 入力長が制限を超えない場合
            {
           input[pos++] = ch; // 入力文字を追加
           putchar(ch); // 画面に文字を表示
           fflush(stdout); // 出力をフラッシュ
            }
            
            /*debug*/
            printf("%d\n",timer);
            /*enddebug*/
            
            loop1--;
            loop2--;
            
        }
        
    }

  return 0;
}
