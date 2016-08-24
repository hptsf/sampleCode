/* Date: 2016-08-23
 * Auth: tombin
 * func: revert the argv[1](string) by word, delete many space to one
 *
 * ./revert "   hello    world   "
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

static char *pBuf = NULL;

static char *do_revert(const char *buf)
{
    int i, j, k;
    int len, step;
    char *pbuf = NULL;

    if(NULL == buf)
        return NULL;

    len = strlen(buf);
    pbuf = (char *)malloc(sizeof(char) * (len + 1));
    if(NULL == pbuf){
        perror("malloc failed");
        return NULL;
    }

    i = len - 1;
    while(i >= 0 && ' ' == buf[i])
        i --;

    j = 0;
    while(i >= 0){
        step = i;
        while(i >= 0 && ' ' != buf[i])
            i--;
        for(k = i + 1; k <= step; k++, j++)
            pbuf[j] = buf[k];

        while(i >= 0 && ' ' == buf[i])
            i --;

        if(i < 0)
            break;
        pbuf[j++] = ' ';
    }

    pbuf[j] = '\0';

    return pbuf;
}

int main(int argc, char *argv[])
{
    if(argc < 2){
        fprintf(stdout, "Usage: cmd string\n");
        return 0;
    }

    fprintf(stdout, "%s.\n", argv[1]);
    pBuf = do_revert(argv[1]);
    if(NULL == pBuf){
        fprintf(stdout, "revert failed\n");
        return 0;
    }

    fprintf(stdout, "%s.\n", pBuf);
    free(pBuf);

    return 0;
}
