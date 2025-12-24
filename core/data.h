#if !defined(COLLECTIVE_PLUS_CORE_DATA_H_)
#define COLLECTIVE_PLUS_CORE_DATA_H_

#define MIN_ARGS_CLI 2
#define MAX_ARGS_CLI_INIT 4
#define MAX_ARGS_CLI_FETCH 2

#define MAIN_COMMAND_SIZE 20
#define INIT_PARAM_SIZE 4
#define PROJECT_PATH_PARAM_SIZE 15
#define CACHE_PATH_PARAM_SIZE 13

const char MAIN_COMMAND[] = "collective_plus_core";
const char INIT_PARAM[] = "init";
const char PROJECT_PATH_PARAM[] = "--project-path=";
const char CACHE_PATH_PARAM[] = "--cache-path=";

#endif