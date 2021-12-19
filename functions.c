#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "funcs.h"
#define TXT 1024
#define WORD 30
int f1(char* word, int wordLen ,char* txt, int txtLen){
    int gimW = 0, gimT = 0, first = 1, jChanged = 1;
    char *wptr = word, *tptrEnd = txt, *tptrStart = txt;
    char curr = 'a';
    char *currWord = txt;
    //init the gimetry of word
    for(int i=0;i<wordLen; ++i){
        curr = wptr[i];
        if('A' <= curr && 'Z' >= curr){
            gimW += (int) curr-'A'+1;
        }
        else if('a' <= curr && 'z' >= curr){
            gimW += (int) curr-'a'+1;
        }
    }
    int i=0, j=0;
    while(j < txtLen&&i < txtLen){
        //check the gimetry of the text between tptrStart and tptrEnd
        if(jChanged){
            curr = tptrEnd[j];
            if('A' <= curr && 'Z' >= curr){
                gimT += (int) curr-'A'+1;
            }
            else if('a' <= curr && 'z' >= curr){
                gimT += (int) curr-'a'+1;
            }
        }
        if(gimW == gimT){ //print the string
            if(isalpha(tptrEnd[j])){
                currWord = &(tptrStart[i]);
                if(first == 0){
                    printf("~");
                } else{
                    first = 0;
                }
                while(currWord != &(tptrEnd[j])+1){
                    printf("%c", *currWord);
                    currWord++;
                }
            }
            j++;
            jChanged = 1;
        }
        if(gimT < gimW){ //add another char
            j++;
            jChanged = 1;
        }
        if(gimT>gimW){//sub the first char and sub it's value from gimT
            curr = tptrStart[i]; 
            if('A' <= curr && 'Z' >= curr){
                gimT = gimT-((int) (curr-'A'+1));
            }
            else if('a' <= curr && 'z' >= curr){
                gimT =gimT-((int) (curr-'a'+1));
            }
            i++;
            while (isalpha(tptrStart[i]) == 0)
            {
                i++;
            }
            jChanged = 0;
        }
    }
    return 1; 
}

void f2(char* word, int wordLen ,char* txt, int txtLen){
    char *atbash = (char*)malloc(wordLen*sizeof(char));
    char *backAtbash = (char*)malloc(wordLen*sizeof(char));
    char *aptr = atbash, *bptr = backAtbash,*tptrEnd = txt, *tptrStart = txt;
    char a= 'a', b='b', c='c';
    int first = 1, j=0, k=0;
    char *curr = (char*)calloc(TXT,sizeof(char));
    if(curr == NULL || atbash == NULL || backAtbash == NULL){
        return;
    }
    //init atbash
    for(int i=0; i<wordLen;++i){
        if('A'<=*(word+i) && *(word+i)<='Z'){
            *(atbash+i) = 'Z' - *(word+i) + 'A';
        }
        else{
            *(atbash+i) = 'z' - *(word+i) + 'a';
        }
    }
    //init backAtbash
    for(int i=0;i<wordLen;++i){
        backAtbash[i]= atbash[wordLen-i-1];
    }
    while(j <=txtLen && k<=txtLen){
        k++;
        while(k <= txtLen && c != a && c != b){//find the first char that is the same
            k++;
            c= *(tptrStart+k);
        }
        if(k > txtLen){
            break;
        }
        if(tptrStart[k] == *aptr){//if the first char is the same as the first char in atbash
            j = k;
            while(*aptr!= 0 && j <= txtLen){//compare chars from the text to chars from atbash
                if(tptrEnd[j] == ' '|| tptrEnd[j] == '\n' || tptrEnd[j] == '\t'){
                    strncat(curr, &(tptrEnd[j]), 1);
                    j++;
                }
                else if(tptrEnd[j] == *aptr){
                    strncat(curr, &(tptrEnd[j]), 1);
                    j++;
                    aptr++;
                }
                else{
                    break;
                }
            }
            if(*aptr == 0){//in case all the chars are the same
                if(first == 0){
                    printf("~");
                }else{
                    first = 0;
                }
                printf("%s", curr);
            }
            free(curr);
            curr = (char*) calloc(TXT, sizeof(char));
            if(curr == NULL){
                return;
            }
        }
        if(tptrStart[k] == *bptr){//if the first char is the same as the first char in backAtbash
            j = k;
            while(*bptr!= '\0' && j < txtLen){//compare chars from the text to chars from backAtbash
                if(tptrEnd[j] == ' '|| tptrEnd[j] == '\n' || tptrEnd[j] == '\t'){
                    strncat(curr, &(tptrEnd[j]), 1);
                    j++;
                }
                else if(tptrEnd[j] == *bptr){
                    strncat(curr, &(tptrEnd[j]), 1);
                    j++;
                    bptr++;
                }
                else{
                    break;
                }
            }
            if(*bptr == '\0'){//in case all the chars are the same
                if(first == 0){
                    printf("~");
                }else{
                    first = 0;
                }
                printf("%s", curr);
            }
            free(curr);
            curr = (char*) calloc(TXT, sizeof(char));
            if(curr == NULL){
                return;
            }
        }
        aptr = atbash;
        bptr = backAtbash;
    }
    free(atbash);
    free(backAtbash);
    free(curr);
    return;
}

struct character
{
    char c;
    int tag;//check if the char c was found in the sequence
};

void f3(char* word, int wordLen, char* txt, int txtLen){
    char *wptr = word, *tptrEnd = txt, *tptrStart = txt, *curr = txt;
    struct character *arr = (struct character*)malloc((wordLen+1)*sizeof(struct character));
    int i =0, flag = 0, first = 1;
    if(arr == NULL){
        return;
    }
    while(*wptr != 0){//init the array with the characters from word
        arr[i].c = *wptr;
        arr[i].tag = 0;
        wptr++;
        i++;
    }
    arr[i].c = '\0';
    arr[i].tag = 0;
    i=0;
    while (*tptrStart != 0 && *tptrEnd != 0)
    {
        while(*tptrStart != 0){//find the beggining of the sequence
            i=0;
            while (arr[i].c != '\0')
            {
                arr[i].tag = 0;
                i++;
            }
            i=0;
            while(arr[i].c != '\0'){//check if current char is in word
                if(*tptrStart == arr[i].c && arr[i].tag == 0){
                    arr[i].tag = 1;
                    flag = 1; 
                    break;
                }
                i++;
            }
            if(flag == 1){
                break;
            }
            tptrStart++;
        }
        if(*tptrStart==0){
            break;
        }
        tptrEnd = tptrStart + 1;
        while(*tptrEnd != 0 && *tptrStart != 0){//find the rest of the sequence
            flag = 0;
            if(*tptrEnd == ' ' || *tptrEnd == '\n' || *tptrEnd == '\t'){
                tptrEnd++;
                continue;
            }
            i=0;
            while(arr[i].c != '\0'){//check if current char is in word
                if(*tptrEnd == arr[i].c && arr[i].tag == 0){
                    arr[i].tag = 1;
                    flag = 1;
                    break;
                }
                i++;
            }
            if(flag == 0){
                break;
            }
            i=0;
            flag = 2;
            while(arr[i].c != '\0'){//check if we found the whole word
                if(arr[i].tag == 0){
                    flag = 1;
                    break;
                }
                i++;
            }
            if(flag == 2){//we found the whole word
                break;
            }
            tptrEnd++;
        }
        if(flag == 2){
            curr = tptrStart;
            if(first == 0){
                printf("~");
            }else{
                first = 0;
            }
            while(curr!=tptrEnd+1){//print the sequence
                printf("%c", *curr);
                curr++;
            }
        }
        tptrStart++;
    }
    free(arr);
    return;
}