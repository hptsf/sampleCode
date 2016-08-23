/* Date: 2016-08-23
 * Auth: tombin
 * func: revert the argv[1](string), delete many space to one
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
    int i;
    int j;
    int k;
    int len;
    char *pbuf = NULL;

    if(NULL == buf)
        return NULL;

    len = strlen(buf);
    pbuf = (char *)malloc(sizeof(char) * (len + 1));
    if(NULL == pbuf){
        perror("malloc failed");
        return NULL;
    }

    i = 0;
    j = len;
    while(i < len && ' ' == buf[i])
        i++;

    while(i < len){
        pbuf[j] = buf[i];
        j --;
        i ++;
        while((i + 1) < len && ' ' == buf[i] && ' ' == buf[i + 1])
            i++;
    }

    j ++;
    if(j <= len && ' ' == pbuf[j])
        j ++;

    for(k = 0; j <= len; j++){
        pbuf[k] = pbuf[j];
        k++;
    }
    pbuf[k] = '\0';

    return pbuf;
}

int main(int argc, char *argv[])
{
    if(argc < 2){
        fprintf(stdout, "Usage: cmd string\n");
        return 0;
    }

    fprintf(stdout, "%s\n", argv[1]);
    pBuf = do_revert(argv[1]);
    if(NULL == pBuf){
        fprintf(stdout, "revert failed\n");
        return 0;
    }

    fprintf(stdout, "%s.\n", pBuf);
    free(pBuf);

    return 0;
}
