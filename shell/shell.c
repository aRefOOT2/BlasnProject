/*

Blasn Kernel Shell version 1.0 PA

*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT 100
#define CURSOR_CHAR '_'

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
    } else if (strcmp(cmd, "exit") == 0)
    {
        return; 
    } else {
        printf("Unknown command: %s\n", cmd);
    }
}

void cursor(int print)
{
    if (print)
    {
        printf("\b%c", CURSOR_CHAR); // カーソル表示
    } else {
        printf("\b "); // カーソル消去
    }
}

int main()
{
    char input[MAX_INPUT];
    int timer = 0;
        int show = 1;

    printf("Welcome to the Blasn kernel shell! Type 'help' for commands.\n");

    while (1)
    {
        printf("blasn> "); // プロンプトを表示

        while (1)
        {
            // カーソル点滅の処理
            if (timer % 50 == 0)
            {
                cursor(show);
                fflush(stdout); // 出力バッファをフラッシュ
                show = !show; // カーソルの表示/非表示を切り替え
            }

                // 入力があったらループを抜ける
                if (fgets(input, sizeof(input), stdin) != NULL)
                {
                    timer = 0;
                } else if (fgets(input, sizeof(input), stdin) == 0x000A)
                {
                    // 改行を削除
                    input[strcspn(input, "\n")] = 0;
                 
                    // コマンドを実行
                    command(input);
                    break;
                }


            timer = 1 + (timer % 1000000);
        }
        
    }

    return 0;
}
