#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"      /* Green */
#define RED     "\033[31m"      /* Red */
#define MAGENTA "\033[35m"      /* Magenta */

void newline() {
	putchar('\n');
}

void print(int x) {
    printf("%d\n", x);
}

void print_bool(int x) {
	if(x) {
		printf("True");
	} else {
		printf("False");
	}
}

int get_int() {
	int input;
	scanf("%d", &input);
	return input;
}

void assertTrue(int expression) {
	assert(expression);
	printf(GREEN "PASSED\n" RESET);
}

void assertFalse(int expression) {
	if(!expression) {
		printf(GREEN "PASSED\n" RESET);
	} else {
		printf(RED "FAILED\n" RESET);
		printf(MAGENTA "expected: " RESET);
		printf(RED "False " RESET);
		printf(MAGENTA "but " RESET);
		printf(GREEN "True " RESET);
		printf(MAGENTA "was found\n" RESET);
		exit(EXIT_FAILURE);
	}
}

void assertEquals(int expected, int value) {
	if(expected == value) {
		printf(GREEN "PASSED\n" RESET);
	} else {
		printf(RED "FAILED\n" RESET);
		printf(MAGENTA "expected: " RESET);
		printf("%d ", expected);
		printf(MAGENTA "but " RESET);
		printf("%d ", value);
		printf(MAGENTA "was found\n" RESET);
		exit(EXIT_FAILURE);
	}
}
