#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

const char* const short_opt = "a:b:c:d:h";
const struct option long_opt[] = {
    {"abs", required_argument, NULL, 'a'},
    {"bless", required_argument, NULL, 'b'},
    {"cros", required_argument, NULL, 'c'},
    {"debug", required_argument, NULL, 'd'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, 0, 0}
};

void print_usage(void)
{
    fprintf(stdout, "--------------------------------------------------\n");
    fprintf(stdout, " -a --abs number for testing abs opt\n");
    fprintf(stdout, " -b --bless for testing bless opt\n");
    fprintf(stdout, " -c --cros for testing cros opt\n");
    fprintf(stdout, " -d --debug for testing debug opt\n");
    fprintf(stdout, " -h --help for testing help opt\n");
    fprintf(stdout, "--------------------------------------------------\n");
}

int main(int argc, char* argv[])
{
    int opt;

    while(-1 != (opt = getopt_long(argc, argv, short_opt, long_opt, NULL))){
        switch(opt){
            case 'a':
                fprintf(stdout, "a is %d\n", atoi(optarg));           /* optarg is global variable */
                break;
            case 'b':
                fprintf(stdout, "b is %s\n", optarg);
                break;
            case 'c':
                fprintf(stdout, "c is %s\n", optarg);
                break;
            case 'd':
                fprintf(stdout, "d is %s\n", optarg);
                break;
            case 'h':
                print_usage();
                break;
        }
    }

    return 0;
}
