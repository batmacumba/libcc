/*
  buffer.h

  A generic buffer interface.
*/

#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <stdlib.h>

// Buffer struct.
typedef struct buffer_s {
  void *data;
  size_t buffer_size;  // Number of members in data array.
  size_t member_size;  // Size of one member.
  size_t p;  // First free position in data.
} Buffer;

/*
  Create and return a new buffer that holds member elements of size
  member_size.
*/
Buffer *buffer_create(size_t member_size);

/*
  Destroy a buffer.
*/
void buffer_destroy(Buffer *B);

/*
  Reset buffer, eliminating contents.
*/
void buffer_reset(Buffer *B);

/*
  Return a valid pointer to the first free position of the
  buffer. This means that, if the space allocated is not enough, then
  the buffer size is increased and the contents are copied.
*/
void *buffer_push_back(Buffer *B);

/*
  Read a line (i.e., reads up to a newline '\n' character or the
  end-of-file) from the input file and places it into the given
  buffer, including the newline character if it is present. The buffer
  is resetted before the line is read.
  Returns the number of characters read; in particular, returns ZERO
  if end-of-file is reached before any characters are read.
*/
int read_line(FILE *input, Buffer *B);

// Some handy abbreviations.
#define buffer_push_char(B, c)  (*((char *) buffer_push_back(B)) = c)

#endif
