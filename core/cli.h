#ifndef COLLECTIVE_PLUS_CORE_CLI_H_
#define COLLECTIVE_PLUS_CORE_CLI_H_

#include <stdbool.h>

typedef struct 
{
    bool init;
    char *project_path;
    char *cache_path;
} cli_opts_t;

int cli_parse(int argc, char *argv[], cli_opts_t *opts);

int cli_validate_paths(const cli_opts_t *opts);

void cli_free(cli_opts_t *opts);

#endif