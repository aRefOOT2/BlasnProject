/*

Blasn Kernel Shell version 1.0.0 A

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/select.h>
#include <termios.h>
#include <dirent.h>
#include <pwd.h>
#include <limits.h>




char* user = "root";
char* hostname = "blasnlive";
char* currentdir = "^";
char* prmpt = "#";




// プロンプト表示部分を更新
void update_prmpt()
{
  char new_dir[PATH_MAX];
  getcwd(new_dir, sizeof(new_dir));

  if (strcmp(new_dir, "/root") == 0)
  {
    
    currentdir = "^"; // カレントディレクトリが/rootの場合
    
  } else
  {
  
    struct passwd *pw = getpwuid(getuid());
    if (strncmp(new_dir, pw->pw_dir, strlen(pw->pw_dir)) == 0)
    {
    
     currentdir = "~"; // ユーザーのホームディレクトリ
    
    } else
    {
     
      currentdir = new_dir; // 絶対パスを表示
      
    }
      
  }
    
}



// cdコマンドの実装
// AIのコードがめんどくさすぎたのでcdコマンドだけ別関数で定義
void cd_cmd(const char *input_path)
{

  char path[PATH_MAX];

    if (input_path && strlen(input_path) > 0)
    {
    
        // 引数がある場合
        strncpy(path, input_path, sizeof(path) - 1);
        path[sizeof(path) - 1] = '\0'; // NULL終端
    
    } else
    {
    
        // 引数がない場合はホームディレクトリを取得
        struct passwd *pw = getpwuid(getuid());
        if (pw)
        {
        
            strncpy(path, pw->pw_dir, sizeof(path) - 1); // ユーザーのホームディレクトリを取得
            path[sizeof(path) - 1] = '\0'; // NULL終端
        
        } else
        {
        
            perror("cd");
            return;
            
        }
        
    }
    

    // ディレクトリを変更
    if (chdir(path) != 0)
    {
    
      perror("cd"); // エラーメッセージを表示
      return;
    
    }

    // カレントディレクトリの更新
    char new_dir[PATH_MAX];
    getcwd(new_dir, sizeof(new_dir));
    currentdir = strdup(new_dir); // 現在のディレクトリを更新

}


void command(const char *cmd)
{

  if (strcmp(cmd, "hello") == 0)
    {
    
        printf("Hello, user!\n");
        
    } else if (strcmp(cmd, "exit") == 0)
    {
    
        printf("[ \x1b[32mInfo\x1b[0m ] Exiting shell...\n");
        exit(0); // プログラムを終了
        
    } else if (strcmp(cmd, "help") == 0)
    {

        printf("+-------------------Help-------------------+");
        printf("|Available commands:                       |\n");
        printf("|  hello   - Greet the user                |\n");
        printf("|  exit    - Exit the shell                |\n");
        printf("|  dir     - Show directory.               |\n");
        printf("|  cd      - Change current directory.     |\n");
        printf("|  help    - Show this help message        |\n");
        printf("|  version - Show this program information.|\n");
        printf("+------------------------------------------+\n");
        
    } else if (strcmp(cmd, "version") == 0)
    {
        printf("+------------------------------------------------+\n");
        printf("|  Blasn Kernel Shell(BKS)  Version 1.0.0 Alpha  |\n");
        printf("|Type 'help' to see available in-kernel commands.|\n");
        printf("+------------------------------------------------+\n");
        
    } else if (strcmp(cmd, "dir") == 0)
    {
    
      struct dirent *de; // ディレクトリエントリの構造体
      DIR *dr = opendir("."); // 現在のディレクトリをオープン
  
      if (dr == NULL)
      {
      
         printf("[ \x1b[31mERROR\x1b[0m ] Could not open current directory\n");
         return;
         
       }

      while ((de = readdir(dr)) != NULL)
      {
      
          // . と .. を除外して表示
          if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
          {
          
              printf("%s\n", de->d_name);
          
          }
          
      }
      
      closedir(dr);
    } else if (strncmp(cmd, "cd ", 3) == 0)
    {
    
        cd_cmd(cmd + 3);
        
    } else if (strcmp(cmd, "cd") == 0)
    {
    
        cd_cmd(NULL); // 引数なしならホームディレクトリ
        
    } else
    {
    
        printf("[ \x1b[31mERROR\x1b[0m ] Unknown command: %s\n", cmd);
        
    }
    
}



void cursor(bool print)
{

    if (print)
    {
    
        printf("|"); // カーソル表示
    
    } else {
    
    printf("\b \b"); // カーソル消去
    
    }
  
}



void clearline(int length)
{

  for (int i = 0; i < length; i++)
  {
    
       printf("\b"); // カーソルを戻して空白を入れて消去
    
   }
    
}



void set_nonblocking_mode()
{

  struct termios newt;
  tcgetattr(0, &newt);
  newt.c_lflag &= ~(ICANON | ECHO); // Canonical modeをオフ、echoをオフ
  tcsetattr(0, TCSANOW, &newt);

}

void reset_terminal_mode()
{

  struct termios newt;
  tcgetattr(0, &newt);
  newt.c_lflag |= (ICANON | ECHO); // Canonical modeをオン、echoをオン
  tcsetattr(0, TCSANOW, &newt);

}




int main()
{

  char input[MAX_INPUT];
  int timer = 0;
  bool show = true;

  
  set_nonblocking_mode();  
  
  printf("\x1b[40m \x1b[41m \x1b[42m \x1b[43m \x1b[44m \x1b[45m \x1b[46m \x1b[47m \x1b[48m");
  printf("\x1b[0mWelcome to the Blasn kernel shell! Type 'version' print this program information, Type 'help' for commands.\n");

  
  while (1)
  {

    update_prmpt();

    printf("%s@%s: %s %s ",user, hostname, currentdir, prmpt); // プロンプトを表示
     
    memset(input, 0, sizeof(input)); // 入力バッファをクリア
    int pos = 0; // 入力位置
  
    while (1)
    {
    
     timer = 1 + (timer % 1000);
     usleep(1000);
       
       // カーソル点滅の処理
     if (timer % 500 == 0)
       {
       
       cursor(show);
       show = !show;
       fflush(stdout);
       
       }
     
     fd_set read_fds;
     struct timeval tv;
  
     FD_ZERO(&read_fds);
     FD_SET(0, &read_fds); // 標準入力を監視
     tv.tv_sec = 0; // 時間の制限なし
     tv.tv_usec = 0;
      
        // 入力があったかを確認
      if (select(1, &read_fds, NULL, NULL, &tv) > 0)
       {
       
        if (!show)
           {
           
          printf("\b"); //すでにカーソルが描画されている場合
          show = !show;
           
           }
           
        timer = 0;
           
        char ch = getchar(); // 1文字ずつ入力を取得
        if (ch == EOF)
           {
           
          continue; // 入力が終わった場合は無視
           
           }
        if (ch == '\n') // 改行が入力された場合
           {
           
          if (pos > 0)
              {
              
             input[pos] = '\0'; // 文字列の終端を設定
             clearline(pos);
             puts("");
             command(input);
              
              }
           break; // 入力ループを抜ける
          } else if (ch == 127 || ch == '\b') // Backspaceが押された場合
              {
              
             if (pos > 0)
                 {
                 
               pos--; // 入力位置を1つ戻す
               printf("\b \b"); // カーソルを消して文字を消去
               fflush(stdout);
                 
                 }
          
          } else if (pos < MAX_INPUT - 1) // 入力長が制限を超えない場合
              {
              
             input[pos++] = ch; // 入力文字を追加
             putchar(ch); // 画面に文字を表示
             fflush(stdout);
              
              }

        }
              
    }
      
  } 


  reset_terminal_mode(); // 終了時に端末を元に戻す


  return 0;
  
}
