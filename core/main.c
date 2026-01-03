#include <stdio.h>
#include <core/cli.h>

#include <stdio.h>

int main(int argc, char *argv[]) {
    cli_opts_t opts = {0};
    int rc = cli_parse(argc, argv, &opts);
    if (rc) {
        fprintf(stderr, "Parse error: %d\n", rc);
        return (int)rc;
    }

    if (!opts.init) {
        fprintf(stderr, "No 'init' command requested. use: init [--project=PATH] [--cache=PATH]\n");
        cli_free(&opts);
        return 0;
    }

    rc = cli_validate_paths(&opts);
    if (rc) {
        fprintf(stderr, "Validation error\n");
        cli_free(&opts);
        return (int)rc;
    }

    printf("Init requested.\n");
    if (opts.project_path) printf("Project path: %s\n", opts.project_path);
    if (opts.cache_path)   printf("Cache path: %s\n", opts.cache_path);

    /* TODO: дальше — логика инициализации */

    cli_free(&opts);
    return 0;
}