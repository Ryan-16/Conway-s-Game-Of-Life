#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
    bool print_statistics = false;
    bool torus = false;
    
    
    for (int arg = 1; arg <= argc; arg ++) {
        // switch on 2nd character of arg ascii val
        
        option = argv[arg][1];

        switch(option)
        {
            case 'i':
                arg ++;
                input_file_name = argv[arg];
                ip1 = fopen(input_file_name, "r");

                if (ip1 == NULL) {
                    return 1;
                }

            case 'o':
                arg ++;
                output_file_name = argv[arg];
                op1 = fopen(output_file_name, "w");

                if (op1 == NULL) {
                    return 1;
                }
            
            case 'g':
                arg ++;
                number_of_generations = atoi(argv[arg]);

            case 's':
                print_statistics = true;

            case 't':
                torus = true;

            default:
                return 1
        }

    }
    
    read_in_file(ip1,&v);
    for (int i = 1; i <= generations; i ++) {
        if (torus) {
            evolve(&v,will_be_alive_torus);
        }
        else {
            evolve(&v,will_be_alive);
        }
    }
    if (print_statistics) {
        print_statistics(&v);
    }
    write_out_file(op1,&v);
    
    return 0;
}
