//
// Created by Felix Halstrup on 06.04.22.
//

#include "client.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]){

    if(argc <= 1){
        perror("No arguments provided");
        exit(1);
    }

    char* message = argv[1];



}
