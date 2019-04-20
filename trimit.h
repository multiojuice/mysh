// 
// File: trimit.h 
// 
// trimit.h declares the function to trim whitespace from possibly
// dynamically allocated C strings.
// 
// @author http://www.xappsoftware.com/wordpress/2013/11/14/a-simple-c-function-to-trim-leading-and-trailing-white-spaces-from-a-string/
// @author bksteele: bks@cs.rit.edu
// 
// // // // // // // // // // // // // // // // // // // // // // // // 

#ifndef TRIMIT_H
#define TRIMIT_H

/// trim trims leading and trailing space from a C string.
/// @param st the C string to trim
/// @return trimmed C string pointer suitable for free, if appropriate.

char * trim( char * st);

#endif // TRIMIT_H

// // // // // // // // // // // // // // // // // // // // // // // //
