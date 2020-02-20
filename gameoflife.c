#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"gol.h"

int main(int argc, char *argv[]){
    

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
