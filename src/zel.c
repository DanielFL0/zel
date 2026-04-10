#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/*
 * constraints:
 * - small codebase
 *      1. under 5k loc
 *      2. single .c file
 *      3. std c89
 * - fast
 *      1. fast to scan and parse large files
 * - performant
 *      1. must produce really good asm
 */

/*
 * defines
 */
#define DEFAULT_STACK_SIZE 512
#define KiB(n) ((u64)(n) << 10)
#define MiB(n) ((u64)(n) << 20)
#define GiB(n) ((u64)(n) << 30)

/*
 * globals
 */
static unsigned char *arena_data;
static size_t arena_buffer_length = DEFAULT_STACK_SIZE;
static size_t arena_offset = 0;

/*
 * typedefs
 */
typedef enum    value_t value_t;    // ast node type
typedef union   sem_t sem_t;        // ast node semantic information
typedef struct  node_t node_t;      // ast node struct

enum value_t {
    ATOM,
    EXPR
};

union sem_t {
    uint64_t    number;
    node_t      *l_exp;
    node_t      *r_exp;
};

struct node_t {
    value_t     val_type;
    sem_t       sem_info;
};

/*
 * function prototypes
 */
size_t align(size_t value, size_t alignment);
void *arena_alloc(size_t size);
void arena_clear(void);

void read_list(void);
void read_expr(void);

void partial_neg(void);
void partial_add(void);
void partial_sub(void);
void partial_exp(void);

/*
 * arena allocator
 */

// samsal3: alignment must be power of 2
size_t align(size_t value, size_t alignment) {
	return (value + alignment - 1) & ~(alignment - 1);
}

void *arena_alloc(size_t size) {
    if (arena_offset + size <= arena_buffer_length) {
        void *ptr = &arena_data[arena_offset];
        // samsal3: gud enough for x64 :)
        arena_offset = align(arena_offset + size, 16);
        memset(ptr, 0, size);
        return ptr;
    }
    return NULL;
}

void arena_clear(void) {
    arena_offset = 0;
}

int main(int argc, char *argv[]) {
    arena_t = malloc(DEFAULT_STACK_SIZE * sizeof(char));
    node_t b = arena_alloc(sizeof(node_t));
    printf("Hello, World!\n");
    return EXIT_SUCCESS;
}