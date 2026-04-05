#include "brackets.h"

void initTable(DynamicTable* table) {
    table->size = 0;
    table->capacity = 10;
    table->positions = (int*)malloc(table->capacity * sizeof(int));
}

void initStaticTable(StaticTable* table) {
    table->size = 0;
}

void addToTable(DynamicTable* table, int position) {
    if (table->size == table->capacity) {
        table->capacity *= 2;
        table->positions = (int*)realloc(table->positions, table->capacity * sizeof(int));
    }
    table->positions[table->size++] = position;
}


void addToStaticTable(StaticTable* table, int position) { 
    if (table->size < MAX_PARENTHESES) {
        table->positions[table->size++] = position;
    }
}
bool isInTable(DynamicTable* table, int position) {
    for (int i = 0; i < table->size; i++) {
        if (table->positions[i] == position) {
            return true;
        }
    }
    return false;
}

bool isInStaticTable(StaticTable* table, int position) {
    for (int i = 0; i < table->size; i++) {
        if (table->positions[i] == position) {
            return true;
        }
    }
    return false;
}

void freeTable(DynamicTable* mismatches) {
    free(mismatches->positions);
}

int getBracketBalance(const char* str) {
    int counter = 0;
    for (int i = 0; str[i] != '\0' && str[i] != '\n'; i++) {
        if (
            str[i] =='(' ||
            str[i] =='[' ||
            str[i] =='{'
            ) {
                counter++;
            }
        else if (
            str[i] ==')' ||
            str[i] ==']' ||
            str[i] =='}'
            ) {
                counter--;
            }
    }
    return counter;
}


void findMismatchedParentheses(const char* str, StaticTable* mismatches) {
    DynamicTable stack;
    initTable(&stack);
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
            addToTable(&stack, i);
        } else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {
            if (stack.size == 0) {
                 addToStaticTable(mismatches, i);
            } else {
                char open = str[stack.positions[stack.size - 1]];
                if ((str[i] == ')' && open == '(') ||
                    (str[i] == '}' && open == '{') ||
                    (str[i] == ']' && open == '[')) { // Matching Pair
                    stack.size--;
                } else {
                    addToStaticTable(mismatches, i);
                    
                }
            }
        }
    }

    while (stack.size > 0) {
        addToStaticTable(mismatches, stack.positions[--stack.size]);
    }

    free(stack.positions);

}



