#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
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
   
    
    for (int arg = 1; arg < argc; arg ++) {
        // switch on 2nd character of arg ascii val
        
        option = argv[arg][1];

        switch(option)
        {
            case 'i':
                arg ++;
                if (arg > argc) {
                    fprintf(stderr, "No input file given\n");
                    return 1;
                }
                input_file_name = argv[arg];
                ip1 = fopen(input_file_name, "r");

                if (ip1 == NULL) {
                    fprintf(stderr, "Could not open input file\n");
                    return 1;
                }
                break;

            case 'o':
                arg ++;
                if (arg > argc) {
                    fprintf(stderr, "No output file given\n");
                    return 1;
                }
                output_file_name = argv[arg];
                op1 = fopen(output_file_name, "w");

                if (op1 == NULL) {
                    fprintf(stderr, "Could not open output file\n");
                    return 1;
                }
                break;
            
            case 'g':
                arg ++;
                if (arg > argc) {
                    fprintf(stderr, "No number of generations given\n");
                    return 1;
                }
                number_of_generations = atoi(argv[arg]);
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
