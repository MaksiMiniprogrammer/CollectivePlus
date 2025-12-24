#include <core/rc.h>
#include <core/cli.h>
#include <core/data.h>

#include <sys/stat.h>
#include <string.h>
#include <errno.h> 
#include <stdio.h>
#include <stdlib.h>

#define EXIT_IF_ERROR(rc) \
do                        \
{                         \
    int ret = rc;         \
    if (ret)              \
    {                     \
        return ret;       \
    }                     \
} while(0)                \


int get_value_arg(const char* str, int str_size, const char* arg, int arg_size, char* value)
{
    if (!str || !arg || !value) 
    {
        return ERROR_EMPTY_PTR;
    }

    if (str_size <= 0 || arg_size <= 0 || str_size < arg_size)
    {
        return ERROR_GET_VALUE_FROM_ARG;
    }

    if (strncmp(str, arg, arg_size))
    {
        return ERROR_GET_VALUE_FROM_ARG;
    }
    
    if (str_size == arg_size)
    {
        value[0] = 0;
        return NO_ERROR;
    }

    int value_size = str_size - arg_size;

    if (value_size > 0) 
    {
        strncpy(value, str + arg_size, value_size);
    }
    value[value_size] = 0;

    return NO_ERROR;
}

int check_path(const char* path)
{
    struct stat file_info;

    if (stat(path, &file_info))
    {
        if (errno == ENOENT)
        {
            return ERROR_DIR_DONT_EXIST;
        }
        return ERROR_BAD_DIR;
    }

    if (!S_ISDIR(file_info.st_mode))
    {
        return ERROR_BAD_DIR;
    }

    return NO_ERROR;
}

int check_init_one_arg_path(const char* argv)
{
    int arg_name_size;
    char* arg_name = NULL;
    if (!strncmp(argv, PROJECT_PATH_PARAM, PROJECT_PATH_PARAM_SIZE))
    {
        arg_name_size = PROJECT_PATH_PARAM_SIZE;
        arg_name = malloc(arg_name_size + 1);
        if (!arg_name)
        {
            return ERROR_MEMORY_ALLOC;
        }
        if (!memcpy(arg_name, PROJECT_PATH_PARAM, arg_name_size))
        {
            free(arg_name);
            return ERROR_FAIL;
        }
        arg_name[arg_name_size] = 0;
    }
    else if (!strncmp(argv, CACHE_PATH_PARAM, CACHE_PATH_PARAM_SIZE))
    {
        arg_name_size = CACHE_PATH_PARAM_SIZE;
        arg_name = malloc(arg_name_size + 1);
        if (!arg_name)
        {
            return ERROR_MEMORY_ALLOC;
        }
        if (!memcpy(arg_name, CACHE_PATH_PARAM, arg_name_size))
        {
            free(arg_name);
            return ERROR_FAIL;
        }
        arg_name[arg_name_size] = 0;
    }
    else
    {
        return ERROR_FAIL;
    }
    int path_size = strlen(argv) - arg_name_size;
    char path[path_size + 1];

    int res = get_value_arg(argv, strlen(argv), arg_name, arg_name_size, path);
    free(arg_name);
    EXIT_IF_ERROR(res);
    EXIT_IF_ERROR(check_path(path));
    return NO_ERROR;
}

int check_init_args(int argc, char *argv[])
{
    if (argc < MIN_ARGS_CLI || argc > MAX_ARGS_CLI_INIT)
    {
        return ERROR_CNT_ARGS_INIT;
    }
    
    if (strncmp(argv[1], INIT_PARAM, INIT_PARAM_SIZE))
    {
        return ERROR_FIRST_ARG_INIT;
    }

    if (argc >= 3)
    {
        if (!strncmp(argv[2], PROJECT_PATH_PARAM, PROJECT_PATH_PARAM_SIZE)
            && !strncmp(argv[2], CACHE_PATH_PARAM, CACHE_PATH_PARAM_SIZE))
        {
            return ERROR_SECOND_ARG_INIT;
        }

        if (argc == 4)
        {
            if(!strncmp(argv[2], argv[3], strlen(argv[2])))
            {
                return ERROR_THIRD_ARG_INIT;
            }

            if (!strncmp(argv[3], PROJECT_PATH_PARAM, PROJECT_PATH_PARAM_SIZE)
                && !strncmp(argv[3], CACHE_PATH_PARAM, CACHE_PATH_PARAM_SIZE))
            {
                return ERROR_THIRD_ARG_INIT;
            }
        }
    }

    return NO_ERROR;    
}

int check_init_paths(int argc, char *argv[])
{
    if (argc < MIN_ARGS_CLI || argc > MAX_ARGS_CLI_INIT)
    {
        return ERROR_CNT_ARGS_INIT;
    }
    if (argc > 2)
    {
        EXIT_IF_ERROR(check_init_one_arg_path(argv[2]));

        if (argc == 4)
        {
            EXIT_IF_ERROR(check_init_one_arg_path(argv[3]));
        }
    }

    return NO_ERROR;
}

int check_all_init(int argc, char *argv[])
{
    EXIT_IF_ERROR(check_init_args(argc, argv));
    EXIT_IF_ERROR(check_init_paths(argc, argv));
    return NO_ERROR;
}

int check_args(int argc, char *argv[])
{
    EXIT_IF_ERROR(check_all_init(argc, argv));
    return NO_ERROR;
}