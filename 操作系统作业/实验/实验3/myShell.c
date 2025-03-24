#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <termios.h>
#include <ctype.h>
#define MAX_CMD_LEN 100
#define MAX_PIPE_CNT 100
int cpid = -1;
int background;
int running_at_background;
int as_son = 0;

#define HISTORY_SIZE 100
char history[HISTORY_SIZE][MAX_CMD_LEN];
int history_index = -1;
int history_cnt = 0;

char line_buffer[MAX_CMD_LEN];
int line_buffer_index = 0;
int line_buffer_cursor = 0;
void cmd_prompt()
{
    printf("\033[2K\rmyShellCommand> ");
    strcpy(line_buffer, "myShellCommand> ");
    line_buffer_index = strlen(line_buffer);
    line_buffer_cursor = line_buffer_index + 1;
    printf("\033[%dG", line_buffer_cursor);
    fflush(stdout);    
}

void history_down()
{
    if (history_index == -1)
    {
        return;
    }
    else
    {
        history_index--;
    }
}

void history_up()
{
    if (history_index < history_cnt - 1)
    {
        history_index++;
        fflush(stdout);
    }
    else
    {
        return;
    }
}

void add_history(char* cmd)
{
    history_cnt++;
    // printf("\n%s", cmd);
    if (history_cnt > HISTORY_SIZE)
    {
        history_cnt = HISTORY_SIZE;
    }
    
    for (int i = history_cnt - 1; i > 0; i--)
    {
        strcpy(history[i], history[i - 1]);
    }
    strcpy(history[0], cmd);
}

void load_history()
{
    if (history_index == -1)
    {
        cmd_prompt();
        return;
    }
    cmd_prompt();
    printf("%s", history[history_index]);
    strcat(line_buffer, history[history_index]);
    line_buffer_index = strlen(line_buffer);
    line_buffer_cursor = line_buffer_index + 1;
    printf("\033[%dG", line_buffer_cursor);
    fflush(stdout);
}


static struct termios orig_termios;

void restore_terminal(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}
void enable_raw_mode(void)
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(restore_terminal);

    raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


void sigint_handler(int sig)
{
    if (as_son == 1)
    {
        exit(1);
    }
    
    if (cpid == 0 && running_at_background == 0)
    {
        exit(1);
    }
    else
    {
        printf("\n");
        cmd_prompt();
    }
}

char* divide_cmd(char** cmd)
{
    if (**cmd == '\n' || **cmd == '\0' || **cmd == '|' || **cmd == '>' || **cmd == '<')
    {
        return NULL;
    }
    while (**cmd == ' ')
    {
        cmd++;
    }
    int len = 0;
    bool mark;
    while ((*cmd)[len] != ' ' && (*cmd)[len] != '\n' && (*cmd)[len] != '\0'&&(*cmd)[len]!='|'&&(*cmd)[len]!='>'&&(*cmd)[len]!='<')
    {
        len++;
    }
    char* cmd_ptr = malloc(len + 1);
    strncpy(cmd_ptr, *cmd, len);
    cmd_ptr[len] = '\0';
    while ((*cmd)[len] == ' ')
    {
        (*cmd) = (*cmd) + 1;
    }

    (*cmd) = (*cmd) + len;

    return cmd_ptr;
}


char* divide_pipe(char** cmd)
{
    if (**cmd == '\n' || **cmd == '\0')
    {
        return NULL;
    }
    int len = 0;
    char* temp_char_ptr = *cmd;
    while ((*cmd)[len] != '|' && (*cmd)[len] != '\0' && (*cmd)[len] != '\n')
    {
        len++;

    }
    char* cmd_ptr = malloc(len + 1);
    strncpy(cmd_ptr, temp_char_ptr, len);
    cmd_ptr[len] = '\0';
    (*cmd) = (*cmd) + len;
    while (**cmd == '|' || **cmd == ' ')
    {
        (*cmd) = (*cmd) + 1;
    }
    return cmd_ptr;
}

char* divide_input(char** cmd)
{
    if (**cmd != '<')
    {
        return NULL;
    }
    while (**cmd == ' ' || **cmd =='<')
    {
        (*cmd) = (*cmd) + 1;
    }
    int len = 0;
    char* temp_char_ptr = *cmd;
    while ((*cmd)[len] != ' ' && (*cmd)[len] != '\0' && (*cmd)[len] != '\n')
    {
        len++;
    }
    char* cmd_ptr = malloc(len + 1);
    strncpy(cmd_ptr, temp_char_ptr, len);
    cmd_ptr[len] = '\0';
    return cmd_ptr;
}

char* divide_output(char** cmd)
{
    if (**cmd != '>')
    {
        return NULL;
    }
    while (**cmd == ' ' || **cmd =='>')
    {
        (*cmd) = (*cmd) + 1;
    }
    int len = 0;
    char* temp_char_ptr = *cmd;
    while ((*cmd)[len] != ' ' && (*cmd)[len] != '\0' && (*cmd)[len] != '\n')
    {
        len++;
    }
    char* cmd_ptr = malloc(len + 1);
    strncpy(cmd_ptr, temp_char_ptr, len);
    cmd_ptr[len] = '\0';
    return cmd_ptr;
}

int run_cmd(char* cmd)
{

    int status;
    char* cmd_ptr = cmd;
    if (!strcmp(cmd, "exit\n"))
    {
        restore_terminal();
        exit(0);
    }
    if (!strcmp(cmd, "exit"))
    {
        restore_terminal();
        exit(0);
    }
    
    if (!strcmp(cmd, "clear\n"))
    {
        printf("\033c");
        return 0;
    }
    if (strchr(cmd, '&') != NULL)
    {
        background = 1;
    }
    char* input_ptr = strchr(cmd, '<');
    char* input_stream;
    char* output_ptr = strchr(cmd, '>');
    char* output_stream;
    char** argv;
    char* program;
    cmd_ptr = cmd;
    program = divide_cmd(&cmd_ptr);
    char* temp_char_ptr = cmd_ptr;
    int argv_cnt = 0;
    while (1)
    {
        char* tempp = divide_cmd(&cmd_ptr);
        if (tempp == NULL)
        {
            break;
        }
        argv_cnt++;
        free(tempp);
    }
    argv = malloc((argv_cnt + 2) * sizeof(char*));
    for (int i = 0; i < argv_cnt; i++)
    {
        argv[i + 1] = divide_cmd(&temp_char_ptr);
    }
    argv[0] = program;
    argv[argv_cnt + 1] = NULL;
    // printf("argv_cnt:%d\n", argv_cnt);
    // printf("program:%s\n", program);
    // printf("argv:\n");
    // for (int i = 0; i < argv_cnt; i++)
    // {
    //     printf("argv%d:%s\n", i, argv[i]);
    // }

    cpid = fork();
    if (cpid == 0)
    {
        as_son = 1;
        if (output_ptr)
        {
            output_stream = divide_output(&output_ptr);
            // printf("output_stream:%s\n", output_stream);
            fflush(stdout);
        }
        if (input_ptr)
        {
            input_stream = divide_input(&input_ptr);
            // printf("input_stream:%s\n", input_stream);
            fflush(stdout);
        }
        if (background == 1)
        {
            running_at_background = 1; 
        }
        if (input_ptr)
        {
            int fd = open(input_stream, O_RDONLY);
            close(0);
            dup(fd);
            close(fd);
        }
        if (output_ptr)
        {
            int fd = open(output_stream, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            close(1);
            dup(fd);
            close(fd);
        }
        execvp(program, argv);
        perror("");
        exit(0);
    }
    else
    {
        if (background == 0)
        {                
            waitpid(cpid, &status, 0);
            for (int i = 0; i < argv_cnt; i++)
            {
                free(argv[i + 1]);
            }
            free(argv);
            free(program);

            // printf("\n");
            fflush(stdout);
            if (as_son)
            {
                exit(0);
            }
        }
    }

    return 0;
}



int piped_run(char* cmd,int pipe_write,int pipe_read)
{
    int status;
    char* cmd_ptr = cmd;
    if (!strcmp(cmd, "exit\n"))
    {
        exit(0);
    }
    if (strchr(cmd, '&') != NULL)
    {
        background = 1;
    }
    char* input_ptr = strchr(cmd, '<');
    char* input_stream;
    char* output_ptr = strchr(cmd, '>');
    char* output_stream;
    char** argv;
    char* program;
    cmd_ptr = cmd;
    program = divide_cmd(&cmd_ptr);
    char* temp_char_ptr = cmd_ptr;
    int argv_cnt = 0;
    while (1)
    {
        char* tempp = divide_cmd(&cmd_ptr);
        if (tempp == NULL)
        {
            break;
        }
        argv_cnt++;
        free(tempp);
    }
    argv = malloc((argv_cnt + 2) * sizeof(char*));
    for (int i = 0; i < argv_cnt; i++)
    {
        argv[i + 1] = divide_cmd(&temp_char_ptr);
    }
    argv[0] = program;
    argv[argv_cnt + 1] = NULL;
    // printf("argv_cnt:%d\n", argv_cnt);
    // printf("program:%s\n", program);
    // printf("argv:\n");
    // for (int i = 0; i < argv_cnt; i++)
    // {
    //     printf("argv%d:%s\n", i, argv[i]);
    // }

    cpid = fork();
    if (cpid == 0)
    {
        as_son = 1;
        if (output_ptr)
        {
            output_stream = divide_output(&output_ptr);
            // printf("output_stream:%s\n", output_stream);
            fflush(stdout);
        }
        if (input_ptr)
        {
            input_stream = divide_input(&input_ptr);
            // printf("input_stream:%s\n", input_stream);
            fflush(stdout);
        }

        if (pipe_write != 0)
        {
            dup2(pipe_write, STDOUT_FILENO);
        }
        if (pipe_read != 0)
        {
            dup2(pipe_read, STDIN_FILENO);
        }

        if (background == 1)
        {
            running_at_background = 1; 
        }
        if (input_ptr)
        {
            int fd = open(input_stream, O_RDONLY);
            close(0);
            dup(fd);
            close(fd);
        }
        if (output_ptr)
        {
            int fd = open(output_stream, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            close(1);
            dup(fd);
            close(fd);
        }
        execvp(program, argv);
        perror("");

        
        exit(0);
    }
    else
    {
        if (background == 0)
        {                
            waitpid(cpid, &status, 0);
            if (pipe_write != 0)
            {
                close(pipe_write);
            }
            if (pipe_read != 0)
            {
                close(pipe_read);
            }
            free(argv);
            free(program);
            // printf("\n");
            if (as_son)
            {
                exit(0);
            }
            fflush(stdout);
        }
    }

    // for (int i = 0; i < argv_cnt; i++)
    // {
    //     free(argv[i + 1]);
    // }
    return 0;
}

int when_need_pipe(char* cmd)
{
    int cmd_cnt = 0;
    char* cmd_ptr = cmd;
    char** cmds = malloc(MAX_PIPE_CNT * sizeof(char*));
    if (strchr(cmd, '|') != NULL)
    {
        while (1)
        {
            char* temp = divide_pipe(&cmd_ptr);
            if (temp == NULL)
            {
                break;
            }
            cmds[cmd_cnt++] = temp;
        }
        // printf("cmds:\n");
        // for (int j = 0; j < cmd_cnt; j++)
        // {
        //     printf("cmd%d:%s\n", j, cmds[j]);
        // }
        fflush(stdout);
    }

    int** pipe_fd = malloc(cmd_cnt * sizeof(int*));

    for (int i = 0; i < cmd_cnt; i++)
    {
        pipe_fd[i] = malloc(2 * sizeof(int));
        pipe(pipe_fd[i]);
    }

    for (int i = 0; i < cmd_cnt; i++)
    {
        if (i == 0)
        {
            piped_run(cmds[i], pipe_fd[i][1], 0);            
        }
        else if (i < cmd_cnt - 1)
        {
            piped_run(cmds[i], pipe_fd[i][1], pipe_fd[i - 1][0]);
        }
        else if (i == cmd_cnt - 1)
        {
            piped_run(cmds[i], 0, pipe_fd[i - 1][0]);
        }
    }
}


int run()
{
    struct sigaction SIGINT_ACT;
    SIGINT_ACT.sa_handler = sigint_handler;
    sigemptyset(&SIGINT_ACT.sa_mask);
    SIGINT_ACT.sa_flags = 0;
    sigaction(SIGINT, &SIGINT_ACT, NULL);
    printf("\033c");

    enable_raw_mode();

    cmd_prompt();
    while (1)
    {
        char c = 0;
        // enable_raw_mode();
        if (read(STDIN_FILENO, &c, 1) == -1)
        {
            continue;
        }

        if (c == '\x1B')
        {
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) != 1)
            {
                continue;
            }
            if (read(STDIN_FILENO, &seq[1], 1) != 1)
            {
                continue;
            }

            if (seq[0] == '[')
            {
                switch (seq[1])
                {
                case 'A':
                    history_up();
                    load_history();
                    break;
                case 'B':
                    history_down();
                    load_history();
                    break;
                }
            }
        }
        else if (c == '\n')
        {
            history_index = -1;
            restore_terminal();
            char cmd[MAX_CMD_LEN];
            strcpy(cmd, line_buffer + 16);
            line_buffer_index = 0;
            line_buffer_cursor = 0;
            add_history(cmd);
            background = 0;
            printf("\n");
            fflush(stdout);
            if (strchr(cmd, '|'))
            {
                when_need_pipe(cmd);
            } 
            else
            {
                run_cmd(cmd);
            }
            enable_raw_mode();
            cmd_prompt();
            if (fileno(stdin) != 0)
            {
                printf("%d",fileno(stdin));
                exit(EXIT_SUCCESS);
            }
        }
        else if (c >= 32 && c <= 126)
        {
            history_index = -1;
            putc(c, stdout);
            line_buffer[line_buffer_index++] = c;
            line_buffer[line_buffer_index] = '\0';
            line_buffer_cursor = line_buffer_index + 1;
            if (line_buffer_index == MAX_CMD_LEN - 1)
            {
                line_buffer_index = 0;
            }
            fflush(stdout);
        }
        else if (c == 127 || c == 8)
        {
            if (line_buffer_cursor > strlen("myShellCommand> ") + 1)
            {
                line_buffer_cursor--;
                line_buffer[line_buffer_cursor] = '\0';
                line_buffer_index--;
                printf("\010 \010");
                fflush(stdout);
                history_index = -1;
            }
        }
        else if (c == -1)
        {
            exit(0);
        }
    }

}

int main(void)
{
    run();
    return 0;
}
