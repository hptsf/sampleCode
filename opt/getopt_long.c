#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

int main(int argc, char **argv)
{
   int opt;
   int digit_optind = 0;
   int option_index = 0;
   char *optstring = "a:b:c::d";
   const struct option long_options[] = {
       {"reqarg", required_argument, NULL, 'r'},
       {"noarg",  no_argument,       NULL, 'n'},
       {"optarg", optional_argument, NULL, 'o'},
       {0, 0, 0, 0}
   };

   while ( (opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1)
   {
#if 0
        printf("\nopt = %c\n", opt);
        printf("optarg = %s\n", optarg);
        printf("optind = %d\n", optind);
        printf("argv[optind - 1] = %s\n",  argv[optind - 1]);
        printf("option_index = %d\n", option_index);
#endif

        switch(opt){
        case 'a':
            fprintf(stdout, "a = %s\n", optarg);
            break;

        case 'b':
            fprintf(stdout, "b = %s\n", optarg);
            break;

        case 'c':
            fprintf(stdout, "c = %s\n", optarg);
            break;

        case ':':
            fprintf(stdout, "Need parameter:%c\n", optopt);
            break;

        case 'd':
            fprintf(stdout, "d = %s\n", optarg);
            break;

        case 'r':
            fprintf(stdout, "r = %s\n", optarg);
            break;

        case 'n':
            fprintf(stdout, "n = %s\n", optarg);
            break;

        case 'o':
            fprintf(stdout, "o = %s\n", optarg);
            break;

        case '?':
            fprintf(stdout, "unknown parameter: %c\n", optopt);
            break;

        default:
            // TODO: should be help tips
            break;
        }
   }

   return 0;
}
