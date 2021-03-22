// File name: cat.h
// Description: Public interface of the cat class

#ifndef CAT_H
#define CAT_H

// Forward declaration
struct cat_t;

// Memory allocator
struct cat_t* cat_new();

// Constructor
void cat_ctor(struct cat_t*);

// Destructor
void cat_dtor(struct cat_t*);

// All behavior functions are inherited from the animal class.

#endif
