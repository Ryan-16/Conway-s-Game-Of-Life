#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"gol.h"

int main(int argc, char *argv[]){

    struct universe v;
    FILE *ip1 = stdin;
    FILE *op1 = stdout;

    char option;
    char *input_file_name;
    char *output_file_name;
    int number_of_generations = 5;
    bool print_statistics_condition = false;
    bool torus = false;

    // options can be repeated but not conflicting
    bool i_option = false;
    bool o_option = false;
    bool g_option = false;
    
    for (int arg = 1; arg < argc; arg ++) {
        // switch on 2nd character of arg ascii val
        
        option = argv[arg][1];
        if (strlen(argv[arg]) != 2) {
            fprintf(stderr, "Unrecognized option\n");
            return 1;
        }

        switch(option)
        {
            case 'i':
                arg ++;
                if (arg > argc) {
                    fprintf(stderr, "No input file given\n");
                    return 1;
                }
               
                if (i_option && (0 != strcmp(input_file_name, argv[arg]))) {
                    fprintf(stderr, "Input file repeated and mismatch\n");
                    return 1;
                }

                input_file_name = argv[arg];
                ip1 = fopen(input_file_name, "r");

                if (ip1 == NULL) {
                    fprintf(stderr, "Could not open input file\n");
                    return 1;
                }
                i_option = true;
                break;

            case 'o':
                arg ++;
                if (arg > argc) {
                    fprintf(stderr, "No output file given\n");
                    return 1;
                }

                if (o_option && (0 != strcmp(output_file_name, argv[arg]))) {
                    fprintf(stderr, "Output file repeated and mismatch\n");
                    return 1;
                }
   
                output_file_name = argv[arg];
                op1 = fopen(output_file_name, "w");

                if (op1 == NULL) {
                    fprintf(stderr, "Could not open output file\n");
                    return 1;
                }
                o_option = true;
                break;
            
            case 'g':
                arg ++;
                if (arg > argc) {
                    fprintf(stderr, "No number of generations given\n");
                    return 1;
                }
                
                for (int i = 0; i < (int) strlen(argv[arg]); i ++){
                    if (argv[arg][i] < '0' || argv[arg][i] > '9') {
                        fprintf(stderr, "Number of generations was not given as a number\n");
                        return 1;
                    }
                }

                if (g_option && (number_of_generations != atoi(argv[arg]))) {
                    fprintf(stderr, "Number of generations repeated and mismatch\n");
                    return 1;
                }

                number_of_generations = atoi(argv[arg]);
                g_option = true;
                break;

            case 's':
                print_statistics_condition = true;
                break;

            case 't':
                torus = true;
                break;

            default:
                fprintf(stderr, "Unrecognized option\n");
                return 1;
        }

    }
    
    read_in_file(ip1,&v);
    for (int i = 1; i <= number_of_generations; i ++) {
        if (torus) {
            evolve(&v,will_be_alive_torus);
        }
        else {
            evolve(&v,will_be_alive);
        }
    }
    write_out_file(op1,&v);
    if (print_statistics_condition) {
        print_statistics(&v);
    }
    
    return 0;
}
