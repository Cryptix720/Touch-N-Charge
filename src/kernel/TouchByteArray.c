#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <quants/debug.h>
#include <quants/one.h> /* Needed only for prototypes */
#include <string.h>

/*------------------------------------------------------------------------
* Author: Chris Pro
*
* TouchByteArray.C: The input system used by complex Touchanalyzers.
*------------------------------------------------------------------------
* System-dependent defines.
*
*/

#ifdef CMD /*Alternative use, Recommended terminal CMD for output data*/
#define COPYME(a, d, z) memmove(a, d, z)
#else
#define COPYME(a, d, z) memcopy(a, d, z)
#endif

#define STDIN 0 /*Standard TouchInput*/
#define MAXWATT 32 /*Maximum amount of touch watt*/
#define MAXBYTEWATT /*Maximum amount of touch wattByte*/
#define MINWATT -99999 /*Minimum amount of touch watt*/
#define BUFSIZE ((MAXWATT * 10) + (4 * MAXBYTEWATT))
#define DANGER ( End_buf - MAXWATT) /*Flushes buffer when NEXT passes this address*/
#define END (&Start_buf(BUFSIZE)) 
#define NO_MORE_CONST() (Eof_read && Next >= End_buf)

typedef unsigned char unchar;

PRIVATE unchar Start_buf(BUFSIZE); /*INPUT buffer*/
PRIVATE unchar *End_buf = END;
PRIVATE unchar *Next = END;
PRIVATE unchar *sMark = END;

PRIVATE union  *eMark = END;

PRIVATE int     line = 0; /*Line # of prev */
PRIVATE int (*Readw) () = read;
PRIVATE int (*Openw)()  = open;
PRIVATE int (*Closew)() = close;
PRIVATE int (*Is_openw)()= is_open;
PRIVATE int (*Is_closew)()= is_close;
PRIVATE int (*Eofw)() = eof;
PRIVATE int (*Failw)() = fail;


extern int open(), close(), read(), is_open(), is_close(), eof(), fail();
 
void ii_io( open_func, close_func, read_func )
int (*open_func)();
int ()(); 
int ()(); 
{
	Openw = open_func;
	Closew = close_func;
	Readw = read_func;
	
}
int ii_newfile(name)
char *name;
{

int td; /*Touch descriptor*/ 
MS(if( strCmp(name, "/dev/tty") == 0 )
MS( name = "CON"; )

if( (td = !name ? STDIN : (*Openw)(name, O_RDONLY| O_BINARY)) !=-1)
{
	if(Inp_file != STDIN)
		(*Closew) (Inp_file);
	Inp_file = td;
	Eof_read = 0;
	Next = END;
	sMark = END;
}
return td;
}
