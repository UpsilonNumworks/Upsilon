#ifndef PYTHON_TEXT_AREA_BRACKETS
#define PYTHON_TEXT_AREA_BRACKETS
#define  MAX_PARENTHESES 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int* positions;
    int size;
    int capacity;
} DynamicTable;

typedef struct {
    int positions[MAX_PARENTHESES];
    int size;
} StaticTable;

void initTable(DynamicTable* table);
void initStaticTable(StaticTable* table);
void addToTable(DynamicTable* table, int position);
void addToStaticTable(StaticTable* table, int position);
bool isInTable(DynamicTable* table, int position);
bool isInStaticTable(StaticTable* table, int position);
void freeTable(DynamicTable* mismatches);
int getBracketBalance(const char* str);
void findMismatchedParentheses(const char* str, StaticTable* mismatches);

#endif