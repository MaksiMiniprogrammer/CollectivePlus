
#define _POSIX_C_SOURCE 200809L
#include <core/cli.h>
#include <core/rc.h>
#include <core/data.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

static bool starts_with(const char *s, const char *prefix, int prefix_size) 
{
    return strncmp(s, prefix, prefix_size) == 0;
}

static int cli_check_path(const char *path) 
{
    if (!path) 
    {
        return ERROR_EMPTY_PTR;
    }
    struct stat st;

    if (stat(path, &st) != 0) 
    {
        if (errno == ENOENT) 
        {
            return ERROR_PATH_NOT_EXIST;
        }
        return ERROR_FAIL;
    }
    if (!S_ISDIR(st.st_mode)) 
    {
        return ERROR_PATH_NOT_DIR;
    }
    return NO_ERROR;
}

static int set_option_dup_check(char **target, const char *value) 
{
    if (!target || !value) 
    {
        return ERROR_EMPTY_PTR;
    }
    if (*target != NULL) 
    {
        return ERROR_DUPLICATE_ARG;
    }
    char *dup = strdup(value);
    if (!dup) 
    {
        return ERROR_MEMORY_ALLOC;
    }
    *target = dup;
    return NO_ERROR;
}

int cli_parse(int argc, char *argv[], cli_opts_t *opts) 
{
    if (!opts) 
    {
        return ERROR_EMPTY_PTR;
    }
    memset(opts, 0, sizeof(*opts));

    for (int i = 1; i < argc; ++i) 
    {
        char *arg = argv[i];
        if (strncmp(arg, INIT_PARAM, INIT_PARAM_SIZE) == 0) 
        {
            opts->init = true;
            continue;
        }

        if (starts_with(arg, PROJECT_PATH_PARAM, PROJECT_PATH_PARAM_SIZE)) 
        {
            const char *equal_sign = strchr(arg, '=');
            if (!equal_sign || *(equal_sign + 1) == '\0') 
            {
                return ERROR_PARSE;
            }
            const char *val = equal_sign + 1;
            if (!val || *val == '\0') 
            {
                return ERROR_PARSE;
            }
            int rc = set_option_dup_check(&opts->project_path, val);
            if(rc)
            {
                return rc;
            }
            continue;
        }
        
        if (starts_with(arg, CACHE_PATH_PARAM, CACHE_PATH_PARAM_SIZE)) 
        {
            const char *equal_sign = strchr(arg, '=');
            if (!equal_sign || *(equal_sign + 1) == '\0') 
            {
                return ERROR_PARSE;
            }
            const char *val = equal_sign + 1;
            if (!val || *val == '\0') 
            {
                return ERROR_PARSE;
            }
            int rc = set_option_dup_check(&opts->cache_path, val);
            if(rc)
            {
                return rc;
            }
            continue;
        }

        return ERROR_PARSE;
    }

    return NO_ERROR;
}

int cli_validate_paths(const cli_opts_t *opts) 
{
    if (!opts) 
    {
        return ERROR_EMPTY_PTR;
    }
    int rc;
    if (opts->project_path) 
    {
        rc = cli_check_path(opts->project_path);
        if (rc != NO_ERROR) 
        {
            return rc;
        }
    }
    if (opts->cache_path) 
    {
        rc = cli_check_path(opts->cache_path);
        if (rc != NO_ERROR) 
        {
            return rc;
        }
    }
    return NO_ERROR;
}

void cli_free(cli_opts_t *opts) 
{
    if (!opts) 
    {
        return;
    }
    free(opts->project_path);
    opts->project_path = NULL;
    free(opts->cache_path);
    opts->cache_path = NULL;
    opts->init = false;
}