/***
* Tests functionality of all Dictionary functions
* compile: g++ -std=c++17 -Wall -o test Dictionary.cpp DictionaryTest.cpp
***/
#include<iostream>
#include<string>
#include"Dictionary.h"

int main(){

    Dictionary blank;
    blank.setValue("b", 5);
    blank.setValue("a", 10);
    blank.setValue("asher", 16);
    blank.setValue("ashe", 15);
    blank.setValue("c", 17);
    blank.setValue("bads", 5);
    blank.setValue("afkg", 10);
    blank.setValue("kjqwr", 16);
    blank.setValue("ashe", 15);
    blank.setValue("ckhaf", 17);
    std::cout<< blank;
    if(blank.contains("hell")){
        printf("\ncontains\n");
    }    
    std::cout<< blank;
    try
    {
        printf("\nvalue of hello: %d\n", blank.getValue("hello"));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    printf("printing the keys using a preorder traversal: \n");
    std::cout << blank.pre_string() << std::endl;

    Dictionary newdict;

    newdict.setValue("hello", 5);
    newdict.setValue("my name is asher", 1);
    if(blank==newdict){
        printf("\nthey are equal\n");
    }else{
        printf("\nthey are not equal\n");
    }
    printf("\nhere\n\n");
    newdict=blank;
    std::cout<< newdict;
    printf("%d", newdict.size());
    newdict.remove("a");
    newdict.remove("afkg");
    printf("\n\n");
    std::cout<< newdict;
    newdict.begin();
    printf("\n\nvalue of current=%d\n", newdict.currentVal());
    newdict.next();
    printf("value of current=%d\n", newdict.currentVal());
    newdict.next();
    printf("value of current=%d\n", newdict.currentVal());
    newdict.next();
    printf("value of current=%d\n", newdict.currentVal());
    newdict.next();
    printf("value of current=%d\n", newdict.currentVal());
    newdict.next();
    printf("value of current=%d\n", newdict.currentVal());
    newdict.next();
    printf("value of current=%d\n", newdict.currentVal());
    printf("\n");
    newdict.prev();
    printf("value of current=%d\n", newdict.currentVal());
    newdict.prev();
    printf("value of current=%d\n", newdict.currentVal());
    newdict.prev();
    printf("value of current=%d\n", newdict.currentVal());
    newdict.prev();
    printf("value of current=%d\n", newdict.currentVal());
    newdict.prev();
    printf("value of current=%d\n", newdict.currentVal());
    newdict.prev();
    printf("value of current=%d\n", newdict.currentVal());
    Dictionary A;
    A.setValue("d", 1);
    A.setValue("b", 5);
    A.setValue("a", 10);
    A.setValue("c", 15);
    A.setValue("f", 20);
    A.setValue("e", 25);
    A.setValue("g", 30);
    A.begin();
    A.remove("a");
    std::cout<<A.pre_string();
    return 0;

    
}