#include <stdio.h>
#include <string.h>
#define TXT 1024
#define WORD 30
void f1(char* word, char* txt){
    int gimW = 0, gimT = 0;
    char *wptr = word, *tptrEnd = txt, *tptrStart = txt;
    char curr = 'a';
    char *currWord = txt;
    printf("Gematria Sequences: ");
    //init the gimetry of word
    for(int i=0;i<strlen(word); ++i){
        curr = wptr[i];
        if('A' <= curr && 'Z' >= curr){
            gimW += (int) curr-'A'+1;
        }
        else if('a' <= curr && 'z' >= curr){
            gimW += (int) curr-'a'+1;
        }
    }
    while(*tptrEnd != '~'){//first sequence
        //check the gimetry of the text between tptrStart and tptrEnd
        curr = *(tptrEnd);
        if('A' <= curr && 'Z' >= curr){
            gimT += (int) curr-'A'+1;
        }
        else if('a' <= curr && 'z' >= curr){
            gimT += (int) curr-'a'+1;
        }
        if(gimW == gimT){ //print the string
            currWord = tptrStart;
            while(currWord != tptrEnd){
                printf("%c", *currWord);
                currWord++;
            }
            break;
        }
        else if(gimT < gimW){ //add another char
            tptrEnd++;
        }
        else{//sub the first char and sub it's value from gimT
            if('A' <= curr && 'Z' >= curr){
                gimT -= (int) *tptrStart-'A'+1;
            }
            else if('a' <= curr && 'z' >= curr){
                gimT += (int) *tptrStart-'a'+1;
            }
            tptrStart++;
        }
    }
    while (*tptrEnd != '~')//rest of the sequences
    {
        //check the gimetry of the text between tptrStart and tptrEnd
        curr = *(tptrEnd);
        if('A' <= curr && 'Z' >= curr){
            gimT += (int) curr-'A'+1;
        }
        else if('a' <= curr && 'z' >= curr){
            gimT += (int) curr-'a'+1;
        }
        if(gimW == gimT){ //print the string
            currWord = tptrStart;
            printf("~");
            while(currWord != tptrEnd){
                printf("%c", *currWord);
                currWord++;
            }
        }
        else if(gimT < gimW){ //add another char
            tptrEnd++;
        }
        else{//sub the first char and sub it's value from gimT
            if('A' <= curr && 'Z' >= curr){
                gimT -= (int) *tptrStart-'A'+1;
            }
            else if('a' <= curr && 'z' >= curr){
                gimT += (int) *tptrStart-'a'+1;
            }
            tptrStart++;
        }
    }   
}

void f2(char* word, char* txt){
    char atbash[strlen(word)], backAtbash[strlen(word)], curr[] = "";
    char *aptr = atbash, *bptr = backAtbash, *tptrEnd = txt+strlen(word)-1, *tptrStart = txt, *wptr = txt;
    printf("Atbash Sequences: ");
    //init atbash
    for(int i=0; i<strlen(word);++i){
        if('A'<=word[i] && word[i]<='Z'){
            atbash[i] = 'A' + 'Z' - word[i];
        }
        else if('a'<=word[i] && word[i]<='a'){
            atbash[i] = 'a' + 'z' - word[i];
        }
        else{
            atbash[i] = word[i];
        }
    }
    //init backAtbash
    for(int i=0;i<strlen(atbash);++i){
        backAtbash[i]= atbash[strlen(atbash)-i-1];
    }
    while(*tptrEnd != '~' && *tptrStart != '~'){//first sequence
        while(*tptrStart != *aptr && *tptrStart != *bptr && *tptrStart != '~'){//find the first char that is the same
            tptrStart++;
        }
        if(*tptrStart == *aptr){//if the first char is the same as the first char in atbash
            tptrEnd = tptrStart;
            while(*aptr!= '\0' && *tptrEnd != '~'){//compare chars from the text to chars from atbash
                if(*tptrEnd == ' '|| *tptrEnd == '\n' || *tptrEnd == '\t'){
                    strncat(curr, tptrEnd, 1);
                    tptrEnd++;
                }
                else if(*tptrEnd == *aptr){
                    strncat(curr, tptrEnd, 1);
                    tptrEnd++;
                    aptr++;
                }
                else{
                    break;
                }
            }
            if(*aptr == '\0'){//in case all the chars are the same
                printf("%s", curr);
            }
            char curr[] = "";
        }
        if(*tptrStart == *bptr){//if the first char is the same as the first char in backAtbash
            tptrEnd = tptrStart;
            while(*bptr!= '\0' && *tptrEnd != '~'){//compare chars from the text to chars from backAtbash
                if(*tptrEnd == ' '|| *tptrEnd == '\n' || *tptrEnd == '\t'){
                    strncat(curr, tptrEnd, 1);
                    tptrEnd++;
                }
                else if(*tptrEnd == *bptr){
                    strncat(curr, tptrEnd, 1);
                    tptrEnd++;
                    aptr++;
                }
                else{
                    break;
                }
            }
            if(*bptr == '\0'){//in case all the chars are the same
                printf("%s", curr);
            }
        }
        char curr[] = "";
        *aptr = atbash;
        *bptr = backAtbash;
    }
    while(*tptrEnd != '~' && *tptrStart != '~'){//not first sequence
        while(*tptrStart != *aptr && *tptrStart != *bptr && *tptrStart != '~'){//find the first char that is the same
            tptrStart++;
        }
        if(*tptrStart == *aptr){//if the first char is the same as the first char in atbash
            tptrEnd = tptrStart;
            while(*aptr!= '\0' && *tptrEnd != '~'){//compare chars from the text to chars from atbash
                if(*tptrEnd == ' '|| *tptrEnd == '\n' || *tptrEnd == '\t'){
                    strncat(curr, tptrEnd, 1);
                    tptrEnd++;
                }
                else if(*tptrEnd == *aptr){
                    strncat(curr, tptrEnd, 1);
                    tptrEnd++;
                    aptr++;
                }
                else{
                    break;
                }
            }
            if(*aptr == '\0'){//in case all the chars are the same
                printf("~%s", curr);
            }
            char curr[] = "";
        }
        if(*tptrStart == *bptr){//if the first char is the same as the first char in backAtbash
            tptrEnd = tptrStart;
            while(*bptr!= '\0' && *tptrEnd != '~'){//compare chars from the text to chars from backAtbash
                if(*tptrEnd == ' '|| *tptrEnd == '\n' || *tptrEnd == '\t'){
                    strncat(curr, tptrEnd, 1);
                    tptrEnd++;
                }
                else if(*tptrEnd == *bptr){
                    strncat(curr, tptrEnd, 1);
                    tptrEnd++;
                    aptr++;
                }
                else{
                    break;
                }
            }
            if(*bptr == '\0'){//in case all the chars are the same
                printf("%s", curr);
            }
            char curr[] = "";
        }
        *aptr = atbash;
        *bptr = backAtbash;
    }
}