#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"gol.h"

int main(int argc, char *argv[]){

    char option;
    char *input_file_name;
    char *output_filename;
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

            case 'o':
                arg ++;
                output_file_name = argv[arg];
            
            case 'g':
                arg ++;
                number_of_generations = atoi(argv[arg]);

            case 's':
                print_statistics = true;

            case 't':
                torus = true;

            default:
                // unrecognized option
        }

    }

    struct universe v; 
    read_in_file(stdin,&v);
    evolve(&v,will_be_alive);
    evolve(&v,will_be_alive);
    evolve(&v,will_be_alive);
    evolve(&v,will_be_alive);
    evolve(&v,will_be_alive);
    write_out_file(stdout,&v);
    return 0;
}
