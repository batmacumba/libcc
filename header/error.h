/*******************************************************************************
 * Error macros
 * Include this header in your file
 ******************************************************************************/
#ifndef _ERROR_H_
#define _ERROR_H_

#define error(msg) fprintf(stderr, msg)
#define exit(msg) { fprintf(stderr, msg); exit(1); }

#endif /* _ERROR_H_ */
