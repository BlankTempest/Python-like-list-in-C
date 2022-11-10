#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

enum dType{
    tChar,
    tInt,
    tLong,
    tFloat,
    tDouble,
    tBool,
    maxTypes,
};

typedef struct node{
    int type;
    union{
        char* vChar;
        int vInt;
        long vLong;
        float vFloat;
        double vDouble;
        bool vBool;
    };
    struct node* next;
}node;

typedef struct{
    int length;
    node* element;
}list;

void initalize(list* list){
    list->length = 0;
    list->element = NULL;
}

void insert(list* list, char* str) {

    list->length+=1;
    node*p = list->element;
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->next = NULL;
    if(p == NULL){
        list->element = node;
    }
    else{
        while(p->next!= NULL){
            p = p->next;
        }
        p->next = node;
    }

    int i = 0;
    int str1=0, flt=0;
    char ch;
    while(ch=str[i]!='\0') {
        //0-9
        if(!(ch>47 && ch<58) && ch!=45){
            str1 = 1;
        }
        //decimal point
        if(!flt && ch==46 && ch!=45){
            flt = 1;
        }
        i++;
    }

    if(!str1 && !flt){
        int sign;
        if(str[0]=='-'){
            sign = -1;
            str++;
        }
        else{
            sign = 1;
        }
        node->type = tInt;

        int sum = 0;
        int j = 0;
        bool isLong = false;
        while(str[j]!='\0'){
            //if num at any time is less than -1, then it has overflown.
            sum*=10;
            sum += str[j]-'0';
            j++;
            if(sum<0){
                isLong = true;
                break;
            }
        }

        int l = 0;
        int sumL = 0;
        if(isLong){
            while(str[l]!='\0'){
                sumL*=10;
                sumL += str[l]-'0';
                l++;
            }
            node->vLong = sumL;
            node->type = tLong;
        }
        else{
            node->vInt = sum*sign;
        }
        
    }
    else if (flt && !str1) {
        int sign;
        if(str[0]=='-'){
            sign = -1;
            str++;
        }
        else{
            sign = 1;
        }
        node->type = tFloat;

        int sum = 0;
        int j = 0;
        bool isDub = false;
        while(str[j]!='\0'){
            if(str[j]=='.'){
                break;
            }
            //if num at any time is less than -1, then it has overflown.
            sum*=10;
            sum += str[j]-'0';
            j++;
            if(sum<0){
                isDub = true;
                break;
            }
            
        }
        if(!isDub){
            int mantissa = 0;
            int mult = 10;
            if(str[j]=='.'){
                while(str[j]!='\0'){
                    mantissa = str[j]-'0';
                    mantissa /= mult;
                    sum+=mantissa;
                    j++;
                    mult*= 10;
                }
            }
        }
        //then add the parts after the decimal point
        int l = 0;
        int sumL = 0;
        if(isDub){
            while(str[l]!='\0'){
                if(str[j]=='.') break;
                sumL*=10;
                sumL += str[l]-'0';
                l++;
            }

            int mantissa = 0;
            int mult = 10;
            if(str[j]=='.'){
                while(str[j]!='\0'){
                    mantissa = str[j]-'0';
                    mantissa /= mult;
                    sumL+=mantissa;
                    j++;
                    mult*= 10;
                }
            }

            node->vDouble = sumL;
            node->type = tDouble;
        }
        else{
            node->vInt = sum*sign;
        }
    }
    else{
        if(i==4){
            if(str[0] == 't' && str[1]=='r' && str[2]=='u' && str[3]=='e') {
                node->type = tBool;
                node->vBool = true;
                return;
            }
        }
        else if(i==5){
            if(str[0] == 'f' && str[1]=='a' && str[2]=='l' && str[3]=='s' && str[4]=='e') {
                node->type = tBool;
                node->vBool = false;
                return;    
            }
        }

        node->type = tChar;
        char* str2 = (char*)malloc(sizeof(char)*1000);
        strcpy(str2,str);
        node->vChar = str2;
    }

}

void insertList(list* list){
    int add = 1;
    printf("enter something already\n");
    while(add){
        char str[1000]; 
        fscanf(stdin,"%s",str);
        insert(list,str);

        printf("keep adding?\n");
        scanf("%d",&add);
    }
}

void display(list*list){
    node* node = list->element;
    for(int i = 0; i < list->length; i++){
        switch(node->type){
            case tBool:
                if(node->vBool) printf("true\n");
                else printf("false\n");
                break;
            case tChar:
                printf("%s\n",node->vChar);
                break;
            case tDouble:
                printf("%lf\n",node->vDouble);
                break;
            case tFloat:
                printf("%f\n",node->vFloat);
                break;
            case tInt:
                printf("%d\n",node->vInt);
                break;
            case tLong:
                printf("%ld\n",node->vLong);
                break;
        }
        node = node->next;
    }
}

int main() {
    list list;
    initalize(&list);
    insertList(&list);
    display(&list);
    return 0;
}
