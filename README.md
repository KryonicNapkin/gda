# gda
Generic dynamic array library written in C11

## Installation

1. Download the library using this command:

```sh
wget https://raw.githubusercontent.com/KryonicNapkin/gda/refs/heads/main/gda.h
```

2. Include it in your C project

```c
/* Top */

#include "gda.h"

/* Rest of the code */
```

3. And DONE!!

## Usage

Every function is called with the ***name*** prefix like: ***name***_function(args);

The possible functions include:

```c
/* da_init() initializes the array with starting capacity set to __INIT_CAP (8) */
da_init(/* name */* da);
/* da_append() appends a value val to the end of the array; if the array doesn't 
 * have enough capacity it will automaticly reallocate the array */
da_append(/* name */ da, /* type */ val);
/* da_append_at() functions exactly like da_append() by you get to specified to 
 * which index it will put val at */
da_append_at(/* name */* da, /* type */ val, int idx);
/* da_append_many() lets you append many values of the same type to da */
da_append_many(/* name */* da, int n, /* type */ ...);
/* da_pop() removes the last item from the array and returns it */
da_pop(/* name */* da);
/* da_get_at() returns and item from the array at the specified location */
da_get_at(/* name */ da, int idx);
/* da_get_val_idx() returns the index of the val that matches the value in the array */
da_get_val_idx(/* name */ da, /* type */ val);
/* da_print() calls the user created print function */
da_print(/* name */ da, void (*print_func)(/* name */));
/* da_reverse() reverses the array values */
da_reverse(/* name */* da);
/* da_left_shift() shifts the array values to the left by 1 */
da_left_shift(/* name */* da);
/* da_left_shift_by() shifts the array values to the left by amount */
da_left_shift_by(/* name */* da, int amount);
/* da_right_shift() shifts the array values to the right by 1 */
da_right_shift(/* name */* da);
/* da_right_shift_by() shifts the array values to the right by amount */
da_right_shift_by(/* name */* da, int amount);
```

The possible macros include:

```c
/* The capacity for initialized array */
#define __INIT_CAP         8
/* The capacity multiplication factor used to calculate new capacity when 
 * reallocating the array */
#define __CAP_MULTI_FACTOR 2
/* the core macro */
#define da_impl(name, type)
```

As an example I'm going to create a dynamic array of **Args** with the type **char\***

```c
#include <stdio.h>

#include "gda.h"

// Implementation
da_impl(Args, char*);

int main(int argc, char* argv[]) {
    // Declaration
    Args args;

    // Initialization
    Args_da_init(&args);

    char* str = "Hello, world!\n";

    // Append str to args
    Args_da_append(&args, str);
    
    // Pop str from the array
    char* hello = Args_da_pop(&args);

    // Print Hello, world!
    printf("%s", hello);

    // Free the array
    Args_da_free(args);

    return 0;
}
```
