// file: trimit.c
// source: http://www.xappsoftware.com/wordpress/2013/11/14/a-simple-c-function-to-trim-leading-and-trailing-white-spaces-from-a-string/
// author: "GG1"
// downloaded by: bksteele, bks@cs.rit.edu
// since: 3/1/2017
// // // // // // // // // // // // // // // // // // // // // // // // 

#include <ctype.h>   // isspace
#include <string.h>  // strlen

#include "trimit.h"

/*+-----------------------------------------------------------+
  | Function name : trim.                                     |
  | Parameters    :                                           |
  |   str         : the string to trim.                       |
  | Return  value : the pointer to the string.                |
  |               : if an error occurs SU_CANNOT_W_BYTE     //not true
  | Description   : Trims leading and trailing white spaces   |
  |                 and return the modified string.           |
  |                 The pointer to the string can be used to  |
  |                 free memory.                              |
  +-----------------------------------------------------------+*/
/// trim leading and trailing whitespace {' ' \t \n \r}
char *trim(char *str)
{
    size_t   len      = 0;
    char     *frontp  = str - 1;   // point off the front
    char     *endp    = NULL;
    if(str==NULL)
        return NULL;
    
    if(str[0]=='\0')
        return str;
    len   =  strlen(str);
    endp  =  str + len;
    
    /* Move the front and back pointers to address the first
       non-whitespace characters from each end.
     */
    while(isspace(*(++frontp)));

    while(isspace(*(--endp)) && endp!=frontp)
        ;
    
    if(str+len-1!=endp)
    {
        *(endp + 1) = '\0';
    }
    else if(frontp!=str && endp==frontp)
    {
        *str = '\0';
    }
    
    /* Shift the string so that it starts at str so that if it's
     * dynamically allocated, we can still free the returned pointer.
     * Note the reuse of endp to mean the front of the string buffer now.
     */
    endp = str;
    if(frontp!=str)
    {
        while(*frontp)
        {
            *endp++ = *frontp++;
        }
        *endp = '\0';
    }
    return str;
}

// // // // // // // // // // // // // // // // // // // // // // // //
