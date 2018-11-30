#include "9cc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* provide a chunk of stuff to flex */
/* it handles unput itself, so we pass in an argument at a time */
/* returns length. バッファにコピーされたデータの長さ */
/* must max >= 2 */
int myinput(char *buf, int max) {
  static unsigned offset = 0;
  int len, copylen;

  if (max < 2) { /* invalid value, should throw error */
    exit(EXIT_FAILURE);
  }

  if (targv >= arglim)
    return 0; /* EOF */

  len = strlen(*targv) - offset; /* amount of current arg */
  if (len >= max)
    copylen = max - 1;
  else
    copylen = len;

  if (copylen > 0)
    memcpy(buf, targv[0] + offset, copylen);

  if (targv[0][offset + copylen] == '\0') { /* end of arg */
    buf[copylen] = ' ';
    copylen++;
    offset = 0;
    targv++;
  } else {
    offset += copylen;
  }

  return copylen;
}
