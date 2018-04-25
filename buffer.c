/*******************************************************************************
 *	buffer.c
 *		A generic buffer implementation.
 ******************************************************************************/

/* Includes & Macros */
#include <stdio.h>
#include "buffer.h"

/*  buffer_create():
 *      Create and return a new buffer that holds member elements of size
 *      member_size.
 */
Buffer *buffer_create(size_t member_size) {
	Buffer *B = (Buffer*) malloc(sizeof(Buffer));
	if (!B) {
		fprintf(stderr, "buffer_create: cannot create new buffer!\n");
		return NULL;
	}
	
	B -> buffer_size = 0;
	B -> member_size = member_size;
	B -> data = NULL;
	B -> p = 0;
	
	return B;
}

/*  buffer_destroy():
 *      Destroy a buffer.
 */
void buffer_destroy(Buffer *B) {
	free(B -> data);
	free(B);
}

/*  buffer_reset():
 *      Reset buffer, eliminating contents.
 */
void buffer_reset(Buffer *B) {
	free(B -> data);
	B -> data = NULL;
	B -> buffer_size = 0;
	B -> p = 0;
}

/*  buffer_push_back():
 *      Return a valid pointer to the first free position of the
 *      buffer. This means that, if the space allocated is not enough, then
 *      the buffer size is increased and the contents are copied.
 */
void *buffer_push_back(Buffer *B) {
	/* increases the buffer size by one member size */
	B -> data = realloc(B -> data, ++B -> buffer_size * B -> member_size);
	void *ptr = (char*) B -> data + ((B -> buffer_size - 1) * B -> member_size);
	B -> p = (size_t) ptr;
	return ptr;
}

/*  read_line():
 *      Read a line (i.e., reads up to a newline '\n' character or the
 *      end-of-file) from the input file and places it into the given
 *      buffer, including the newline character if it is present. The buffer
 *      is resetted before the line is read.
 *      Returns the number of characters read; in particular, returns ZERO
 *      if end-of-file is reached before any characters are read.
 */
int read_line(FILE *input, Buffer *B) {
	buffer_reset(B);
	int n = 0;
	int c = fgetc(input);
	while (c != EOF) {
		buffer_push_char(B, c);
		n++;
		if (c == 10) break;
		c = fgetc(input);
	}
    return n;
}
