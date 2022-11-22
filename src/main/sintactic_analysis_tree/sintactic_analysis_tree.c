#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sintactic_analysis_tree.h"
#include "../utils/utils.h"

int arithmeticOperation(char * operation);
int booleanOperation(char * operation);
int asignType(struct TreeNode * tree);
int ifType(struct TreeNode * tree);
int checkOperationsTypes(struct TreeNode * tree);
int arithmeticType(struct TreeNode * tree);
int booleanType(struct TreeNode * tree);
int angleBracketsType(struct TreeNode * tree);
int equalType(struct TreeNode * tree);
int whileType(struct TreeNode * tree);

int typeErrors = 0;
types typeMethod;
struct ParameterList *paramList;

struct TreeNode * CreateEmptyNode() {
    struct TreeNode *newNode;

    newNode = (struct TreeNode *) malloc (sizeof(struct TreeNode));
    if(newNode == NULL){
        printf("-> ERROR: couldn't create tree node, exiting\n");
        exit(EXIT_FAILURE);
    }
    else{
        return newNode;
    }
}

SintacticAnalysisTree * CreateEmptyTree() {
    SintacticAnalysisTree *newTree = NULL;

    newTree = (SintacticAnalysisTree *) malloc (sizeof(SintacticAnalysisTree));
    if(newTree == NULL){
        printf("-> ERROR: couldn't create tree node, exiting\n");
        exit(EXIT_FAILURE);
    }
    else{
        return newTree;
    }
}

struct TreeNode * createNode(Symbol *symbol) {

    struct TreeNode *newNode = CreateEmptyNode();
    newNode->info = symbol;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct TreeNode * createTree(Symbol *symbol, struct TreeNode *left, struct TreeNode *right) {
    
    if(right == NULL && left == NULL){
        return NULL;
    }
    
    struct TreeNode *newNode = CreateEmptyNode();
    newNode->info = symbol;
    newNode->right = right;
    newNode->left = left;
    return newNode;
}

void getTreeInOrder(struct TreeNode *tree, char * s) {
    if(tree == NULL){
        return;
    }
    getTreeInOrder(tree->left, s);
    strcat(s, " ");
    strcat(s, tree->info->name);
    getTreeInOrder(tree->right, s);
    
}

void printTreeInOrder(struct TreeNode *tree) {
    if(tree == NULL){
        return;
    }
    printTreeInOrder(tree->left);
    printf(" %s", tree->info->name);
    printTreeInOrder(tree->right);
    
}

int checkOperationsTypes(struct TreeNode * tree){

    if(strcmp(tree->info->name, "if") == 0){
        return ifType(tree);
    }
    else if(strcmp(tree->info->name, "=") == 0){
        return asignType(tree);
    }
    else if(strcmp(tree->info->name, "==") == 0){
        return equalType(tree);
    }
    else if(strcmp(tree->info->name, "while") == 0){
        return whileType(tree);
    }
    else if(arithmeticOperation(tree->info->name) != 0){
        return arithmeticType(tree);
    }
    else if(booleanOperation(tree->info->name) != 0){
        return booleanType(tree);
    }


}

int whileType(struct TreeNode * tree){
    if(tree->left->info->type != TYPEBOOL){
        printf("\033[0;31m-> ERROR:\033[0m Incompatible types for %s: %s cannot be converted to bool\n", tree->info->name, enumToString(tree->left->info->type));
        exit(0);        
    }

    return 1;
}

int equalType(struct TreeNode * tree){
    if(tree->left->info->type != tree->right->info->type){
        printf("\033[0;31m-> ERROR:\033[0m Conflicting types for: =\nexpected: %s = %s\nfound: %s = %s \n", enumToString(tree->left->info->type), enumToString(tree->left->info->type), enumToString(tree->left->info->type), enumToString(tree->right->info->type));
        exit(0);
    }
    
    tree->info->type = TYPEBOOL;
}

int asignType(struct TreeNode * tree){
    
    if(tree->left->info->type != tree->right->info->type){
        printf("\033[0;31m-> ERROR:\033[0m Conflicting types for: =\nexpected: %s = %s\nfound: %s = %s \n", enumToString(tree->left->info->type), enumToString(tree->left->info->type), enumToString(tree->left->info->type), enumToString(tree->right->info->type));
        exit(0);
    }
    tree->info->type = tree->left->info->type;
    
    return 1;
}

int ifType(struct TreeNode * tree){
    if(tree->left->info->type != TYPEBOOL){
        printf("\033[0;31m-> ERROR:\033[0m Incompatible types for %s: %s cannot be converted to bool\n", tree->info->name, enumToString(tree->left->info->type));
        exit(0);
    }
    return 1;
}

int angleBracketsType(struct TreeNode * tree){
    if(tree->left->info->type != TYPEINT || tree->right->info->type != TYPEINT){
        printf("\033[0;31m-> ERROR:\033[0m Incompatible types for %s operation\nexpected: INT %s INT\nfound: %s %s %s \n", tree->info->name, tree->info->name, enumToString(tree->left->info->type), tree->info->name, enumToString(tree->right->info->type));
        exit(0);
    }

    tree->info->type = TYPEBOOL;
    return 1;
}

int arithmeticType(struct TreeNode * tree){
    if(tree->left->info->type != tree->right->info->type){
        printf("\033[0;31m-> ERROR:\033[0m Incompatible types for %s operation\nexpected: INT %s INT\nfound: %s %s %s \n", tree->info->name, tree->info->name, enumToString(tree->left->info->type), tree->info->name, enumToString(tree->right->info->type));
        exit(0);   
    }
    
    tree->info->type = TYPEINT;
    return 1;
}

int booleanType(struct TreeNode * tree){
    
    if(strcmp(tree->info->name, "<") == 0 || strcmp(tree->info->name, ">") == 0){
        return angleBracketsType(tree);
    }

    if(tree->left->info->type != tree->right->info->type){
        printf("\033[0;31m-> ERROR:\033[0m Incompatible types for %s operation\nexpected: BOOL %s BOOL\nfound: %s %s %s \n", tree->info->name, tree->info->name, enumToString(tree->left->info->type), tree->info->name, enumToString(tree->right->info->type));
        exit(0);        
    }

    tree->info->type = TYPEBOOL;
    return 1;
}

int checkTypeTree(struct TreeNode *tree) {
    int validTree = 1;

    if(tree == NULL){
        return 1;
    }
    
    if(tree->right != NULL && tree->right->info->type == UNDEFINED && strcmp(tree->right->info->name, "next") != 0){                
        validTree = validTree && checkTypeTree(tree->right);
    }

    if(tree->left != NULL && tree->left->info->type == UNDEFINED){
        validTree = validTree && checkTypeTree(tree->left);  
    }
    
    if(tree->left != NULL && tree->left->info->it == METHOD){
        typeMethod = tree->left->info->type;
        validTree = validTree && checkTypeTree(tree->left);
        
        
        // Check return in methods

        // if(tree->left->info->type != TYPEVOID || tree->left->info->type != UNDEFINED){
        //     if(tree->left->left != NULL && checkReturnInMethod(tree->left->left) == 0){
        //         printf("IF: %d\n", checkIfInMethod(tree->left->left));
        //         printf("IFELSE: %d\n", checkIfElseInMethod(tree->left->left));
        //         if(checkIfInMethod(tree->left->left) == 0 && checkIfElseInMethod(tree->left->left) == 0){
        //             printf("\033[0;31m-> ERROR:\033[0m Method %s without return\n", tree->left->info->name);
        //             exit(0);
        //         }
        //     }
        // }
    }

    if(tree->left != NULL && tree->left->info->it == METHODCALL && tree->left->info->parameterList != NULL){
        if(tree->left->info->parameterList->head != NULL && tree->left->left == NULL){
            printf("\033[0;31m-> ERROR:\033[0m Too few arguments to method %s\n", tree->left->info->name);
            exit(0);
        }
        if(countExp(tree->left->left, 0) > sizeParameter(tree->left->info->parameterList->head)){
            printf("\033[0;31m-> ERROR:\033[0m Too many arguments to method %s\n", tree->left->info->name);
            exit(0);
        }

        if(tree->left->left != NULL){
            validTree = validTree && checkTypeTree(tree->left->left);
            validTree = validTree && checkParameters(tree->left->left, tree->left->info->parameterList->head, tree->left->info->name);
        }
    }

    if(tree->right != NULL && tree->right->info->it == METHODCALL && tree->right->info->parameterList != NULL){
        if(tree->right->info->parameterList->head != NULL && tree->right->left == NULL){
            printf("\033[0;31m-> ERROR:\033[0m Too few arguments to method %s\n", tree->right->info->name);
            exit(0);
        }

        if(countExp(tree->right->left, 0) > sizeParameter(tree->right->info->parameterList->head)){
            printf("\033[0;31m-> ERROR:\033[0m Too many arguments to method %s\n", tree->right->info->name);
            exit(0);
        }
        
        if(tree->right->left != NULL){
            validTree = validTree && checkTypeTree(tree->right->left);
            validTree = validTree && checkParameters(tree->right->left, tree->right->info->parameterList->head, tree->right->info->name);
        }
    }
    
    if(strcmp(tree->info->name, "next") != 0 && tree->left != NULL && tree->right != NULL){
        
        validTree = validTree && checkOperationsTypes(tree);
    }
    
    if(strcmp(tree->info->name, "-") == 0){
        if(tree->left->info->type != TYPEINT){
            printf("\033[0;31m-> ERROR:\033[0m Incompatible types for %s: %s cannot be converted to int\n", tree->info->name, enumToString(tree->left->info->type));
            exit(0);  
        }

        tree->info->type = TYPEINT;
    }

    if(strcmp(tree->info->name, "!") == 0){
        if(tree->left->info->type != TYPEBOOL){
            printf("\033[0;31m-> ERROR:\033[0m Incompatible types for %s: %s cannot be converted to %s\n", tree->info->name, enumToString(tree->left->info->type), enumToString(TYPEBOOL));         
            exit(0);             
        }
        tree->info->type = tree->left->info->type;
    }

    if(strcmp(tree->info->name, "return") == 0){
        
        checkOperationsTypes(tree->right);
        tree->info->type = tree->right->info->type;
        if(tree->info->type != typeMethod){
            printf("\033[0;31m-> ERROR:\033[0m Incompatible types for %s: %s cannot be converted to %s\n", tree->info->name, enumToString(tree->info->type), enumToString(typeMethod));         
            exit(0);
        }
    }

    if(tree->right != NULL && strcmp(tree->right->info->name, "next") == 0){
        checkTypeTree(tree->right);
    }

    return validTree;
}   

int checkParameters(struct TreeNode *tree,  struct ParameterNode *list, char *methodName){

    if(tree->left != NULL && tree->left->info->type != UNDEFINED){
        if(tree->left->info->type != list->info->type){
            printf("\033[0;31m-> ERROR:\033[0m Incompatible types for %s: %s cannot be converted to %s\n", tree->left->info->name, enumToString(tree->left->info->type), enumToString(list->info->type));
            exit(0);
        }
    }

    if(list->next != NULL && tree->right == NULL){
        printf("\033[0;31m-> ERROR:\033[0m Too few arguments to method %s\n", methodName);
        exit(0);
    }
    
    if(list->next != NULL && tree->right != NULL && strcmp(tree->right->info->name, "next") == 0){
        checkParameters(tree->right, list->next, methodName);
    }
        
}

int countExp(struct TreeNode *tree, int count){
    if(tree->left != NULL){
        count = count + 1;
    }
     
    if(tree->right != NULL){
        return countExp(tree->right, count);
    }

    return count;
}

// Functions to check return in methods

// int checkReturnInMethod(struct TreeNode *tree){

//     if(tree->left != NULL && strcmp(tree->left->info->name, "return") == 0){
//         return 1;
//     }
    
//     if(tree->left != NULL && strcmp(tree->left->info->name, "return") != 0 && tree->right != NULL){
//         return checkReturnInMethod(tree->right);
//     }

//     if(tree->right == NULL){
//         return 0;
//     }
// }

// int checkIfElseInMethod(struct TreeNode *tree){
//     if(tree->left != NULL && strcmp(tree->left->info->name, "if") == 0 && tree->left->info->it == IF_ELSE){
//         // printf("paso\n");
//         // printf("EL IF DEL IFELSE: %d\n", checkReturnInIf(tree->left->right->left));
//         // printf("tree: %s\n", tree->left->right->left->right->left->info->name);
//         if(tree->left->right != NULL && tree->left->right->left != NULL && checkReturnInIf(tree->left->right->left) == 1){
//             printf("paso\n");
//             if(tree->left->right != NULL && tree->left->right->right != NULL && checkReturnInElse(tree->left->right->right) == 1){
//                 return 1;
//             }
//         }
//     }

//     if(tree->right != NULL){
//         return checkIfElseInMethod(tree->right);
//     }

//     return 0;
// }

// int checkReturnInElse(struct TreeNode *tree){
//     if(tree->left != NULL && strcmp(tree->left->info->name, "return") == 0){
//         return 1;
//     }

//     if(tree->left != NULL && strcmp(tree->left->info->name, "if") == 0 && tree->left->info->it == IF_){
//         if(tree->left->right != NULL){
//             return checkReturnInIf(tree->left->right);
//         }
//     }

//     if(tree->left != NULL && strcmp(tree->left->info->name, "if") == 0 && tree->left->info->it == IF_ELSE){
//         if(tree->left->right != NULL && tree->left->right->left != NULL && checkReturnInIf(tree->left->right->left) == 1){
//             if(tree->left->right != NULL && tree->left->right->right != NULL && checkReturnInElse(tree->left->right->right) == 1){
//                 return 1;
//             }
//         }
//     }

//     if(tree->right != NULL){
//         return checkReturnInElse(tree->right);
//     }

//     return 0;
// }


// int checkIfInMethod(struct TreeNode *tree){

//     if(tree->left != NULL && strcmp(tree->left->info->name, "if") == 0 && tree->left->info->it == IF_){
//         if(tree->left->right != NULL && checkReturnInIf(tree->left->right) == 1){
//             return 1;
//         }   
//     }

//     if(tree->right != NULL){
//         return checkIfInMethod(tree->right);    
//     }

//     return 0;
// }

// int checkReturnInIf(struct TreeNode *tree){

//     if(tree->left != NULL && strcmp(tree->left->info->name, "return") == 0){
//         printf("aca return\n\n\n");
//         return 1;
//     }

//     if(tree->left != NULL && strcmp(tree->left->info->name, "if") == 0 && tree->left->info->it == IF_){
//         if(tree->left->right != NULL){
//             return checkReturnInIf(tree->left->right);
//         }
//     }

//     if(tree->left != NULL && strcmp(tree->left->info->name, "if") == 0 && tree->left->info->it == IF_ELSE){
//         if(tree->left->right != NULL && tree->left->right->left != NULL && checkReturnInIf(tree->left->right->left) == 1){
//             if(tree->left->right != NULL && tree->left->right->right != NULL && checkReturnInElse(tree->left->right->right) == 1){
//                 return 1;
//             }
//         }
//     }
    
//     if(tree->right != NULL){
//         return checkReturnInIf(tree->right);
//     }

//     return 0;
// }
