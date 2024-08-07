#include "cachelab.h"
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define uint_32max 1 << 31;
// finish the block of getting the command arguments

struct cache_line{
    int valid_bit;
    int tag;
    int LRU_counter;
}cache_line;

struct result{
    int hit;
    int miss;
    int eviction;
}result;

typedef struct cache_line *cache_line_entry;
typedef cache_line_entry *cache_set_entry;

void usage(){
    printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n");
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n\n");
    printf("Examples:\n");
    printf("  linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace\n");
    printf("  linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");

}


void update_result(char I,unsigned int address,cache_set_entry cache,int sets,int E,int b,int v){
    unsigned set_index_cast = (1 << sets) -1;

    unsigned set_index = address >> b & set_index_cast;

    unsigned tag = address >> (sets+b);

    int evict_true = 1;

    unsigned smallest_LRU= uint_32max; //first initliaze, 
    unsigned replaced_LRU_index;

    unsigned largest_LRU = 0;
    // printf("%d %d \n", set_index, tag);
    // load or store, trigger once

    for (int i = 0; i < E;i++){
        if(cache[set_index][i].valid_bit == 0){
            //if there is empty line, no need to evict
            evict_true = 0;
            replaced_LRU_index = i;
            break;
        }
        else
        {
            if(cache[set_index][i].LRU_counter <= smallest_LRU){
                smallest_LRU = cache[set_index][i].LRU_counter;
                replaced_LRU_index = i;
            }
        }
    }

    for (int i = 0; i < E;i++){
        if(cache[set_index][i].LRU_counter > largest_LRU){
            largest_LRU = cache[set_index][i].LRU_counter;
        }
    }

        for (int i = 0; i < E; i++)
        {
            if (cache[set_index][i].tag == tag && cache[set_index][i].valid_bit == 1)
            {
                // found
                result.hit++;
                if(v){
                    if (I != 'M')
                    {
                        printf(" hit\n");
                    }
                    else if (I == 'M')
                    {
                        printf(" hit");
                    }
                }


                // tmr question, how to handle LRU
                cache[set_index][i].LRU_counter = largest_LRU + 1;
                return;
            }
        }
    //didn't find, miss++ and determine if need to evict

    result.miss++;
    
    if (evict_true)
    {
        if(v){
            if(I == 'M'){
                printf(" miss eviction");
            }else{
                printf(" miss eviction\n");
            }
        }


        result.eviction++;
        cache[set_index][replaced_LRU_index].tag = tag;
        cache[set_index][replaced_LRU_index].valid_bit = 1;
        cache[set_index][replaced_LRU_index].LRU_counter = largest_LRU + 1;
    }
    else
    {
        if(v){
            if(I == 'M'){
                printf(" miss");
            }else{
                printf(" miss\n");
            }
        }

        
        cache[set_index][replaced_LRU_index].tag = tag;
        cache[set_index][replaced_LRU_index].valid_bit = 1;
        cache[set_index][replaced_LRU_index].LRU_counter = largest_LRU + 1;
    }

}

void read_file(char* file,cache_set_entry cache,int sets,int E,int b,int v){
    FILE *pFile;
    char identifier;
    unsigned address; //unsigned int
    int size;


    pFile = fopen(file, "r");
    while (fscanf(pFile," %c %x,%d",&identifier,&address,&size)>0)
    {
        /* code */
        
        if(identifier == 'L' || identifier =='S'){
            if(v){
                printf("%c %x,%d", identifier, address, size);
            }
            
            update_result(identifier, address, cache, sets, E, b,v);
        }else if(identifier =='M'){
            if(v){
                printf("%c %x,%d", identifier, address, size);
            }
            update_result(identifier, address, cache, sets, E, b,v);
            update_result('R', address, cache, sets, E, b,v);
        }

        // doing actual code here

    }
    fclose(pFile);
}




cache_set_entry cache_init(int sets,int E){
    int e = pow(2, sets); // equivalent to 1 << sets;
    // printf("%d", e);
    cache_set_entry cache = (cache_set_entry)malloc(e * sizeof(cache_line_entry));
    //first allocate the memory of sets
    for (int i = 0; i < e;i++){
        cache[i] = (cache_line_entry)calloc(E , sizeof(cache_line));
    }
    return cache;
}

void free_memory(cache_set_entry cache,int sets){
    for (int i = 0; i < sets;i++){
        free(cache[i]);
    }
    free(cache);
}

int main(int argc,char** argv)
{
    //get the arguments

    int opt, v = 0, s, e, b;
    char* file;
    cache_set_entry cache;
    // the file initiliazer

    while(-1 != (opt = getopt(argc,argv,"hvs:E:b:t:"))){
        switch(opt){
            case 'h':
                usage();
                return 0;
            case 'v':
                v = 1;
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                e = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                file = (optarg);
                // printf("%s",file);
                break;
            default:
                usage();
                break;
        }
    }
    //allocate memory
    //question, how to set the index bit in the cache?
    //s is used to define 
    // cache[S][E], S = 2^s, 
    cache = cache_init(s,e);

    // for (int i = 0; i < s;i++){
    //     for (int j = 0; j < e;j++){
    //         printf("%d  %d \n",j, cache[i][j].valid_bit);
    //     }
    // }
    read_file(file,cache,s,e,b,v);

    printSummary(result.hit, result.miss, result.eviction);
    free_memory(cache,s);
    return 0;
}
