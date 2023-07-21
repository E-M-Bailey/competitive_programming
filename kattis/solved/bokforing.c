#define DO_TIME 0

#pragma GCC optimize("Ofast")

#if DO_TIME
#include <time.h>
#endif
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>

#define BUFS 3600014u
#define OUTS 1200000u

unsigned A[1000001], n = 0, q = 0, tim = 0, def = 0, i, x;
char *in_ptr, BUF[OUTS], *out_ptr = BUF;

#if DO_TIME
struct timespec ta, tb, tc, td;
#endif

int main()
{
    #if DO_TIME
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ta);
    #endif
    in_ptr = (char *)mmap(0, BUFS, PROT_READ, MAP_SHARED | MAP_POPULATE, STDIN_FILENO, 0);
    madvise(in_ptr, BUFS, MADV_SEQUENTIAL);
    madvise(in_ptr, BUFS, MADV_WILLNEED);
    madvise(in_ptr, BUFS, MADV_HUGEPAGE);
    madvise(in_ptr, BUFS, MADV_POPULATE_READ);    

    #if DO_TIME
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tb);
    #endif

    do
        n = 10 * n + *in_ptr - '0';
    while (*++in_ptr != ' ');
    ++in_ptr;
    do
        q = 10 * q + *in_ptr - '0';
    while (*++in_ptr != '\n');

    while (q--)
    {
        switch (*++in_ptr)
        {
        case 'S':
            if (i = *(in_ptr += 4) - '0', *++in_ptr != ' ')
                if (i = i * 10u + *in_ptr++ - '0', *in_ptr != ' ')
                    if (i = i * 10u + *in_ptr++ - '0', *in_ptr != ' ')
                        if (i = i * 10u + *in_ptr++ - '0', *in_ptr != ' ')
                            if (i = i * 10u + *in_ptr++ - '0', *in_ptr != ' ')
                                if (i = i * 10u + *in_ptr++ - '0', *in_ptr != ' ')
                                    i = i * 10u + *in_ptr++ - '0';
            if (x = *++in_ptr - '0', *++in_ptr != '\n')
                if (x = x * 10u + *in_ptr++ - '0', *in_ptr != '\n')
                    if (x = x * 10u + *in_ptr++ - '0', *in_ptr != '\n')
                        if (x = x * 10u + *in_ptr++ - '0', *in_ptr != '\n')
                            x = x * 10u + *in_ptr++ - '0';
            A[i] = tim | x;
            break;

        case 'R':
            if (def = *(in_ptr += 8) - '0', *++in_ptr != '\n')
                if (def = def * 10u + *in_ptr++ - '0', *in_ptr != '\n')
                    if (def = def * 10u + *in_ptr++ - '0', *in_ptr != '\n')
                        if (def = def * 10u + *in_ptr++ - '0', *in_ptr != '\n')
                            def = def * 10u + *in_ptr++ - '0';
            tim += 0x4000u;
            break;

        case 'P':
            if (i = *(in_ptr += 6) - '0', *++in_ptr != '\n')
                if (i = i * 10u + *in_ptr++ - '0', *in_ptr != '\n')
                    if (i = i * 10u + *in_ptr++ - '0', *in_ptr != '\n')
                        if (i = i * 10u + *in_ptr++ - '0', *in_ptr != '\n')
                            if (i = i * 10u + *in_ptr++ - '0', *in_ptr != '\n')
                                if (i = i * 10u + *in_ptr++ - '0', *in_ptr != '\n')
                                    i = i * 10u + *in_ptr++ - '0';

            x = A[i];
            i = x = (x & 0xffffc000u) == tim ? (x & 0x3fffu) : def;

            if (x == 10000)
                goto O5;
            else if (x >= 1000)
                goto O4;
            else if (x >= 100)
                goto O3;
            else if (x >= 10)
                goto O2;
            else
                goto O1;

        O5: *out_ptr++ = '1';
            i -= 10000;
        O4: *out_ptr++ = (char)(i / 1000 + '0');
            i %= 1000;
        O3: *out_ptr++ = (char)(i / 100 + '0');
            i %= 100;
        O2: *out_ptr++ = (char)(i / 10 + '0');
            i %= 10;
        O1: *out_ptr++ = (char)(i + '0');
            *out_ptr++ = '\n';
            break;

        default:
            __builtin_unreachable();
        }
    }
    #if DO_TIME
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tc);
    #endif

    write(STDOUT_FILENO, BUF, out_ptr - BUF);

    #if DO_TIME
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &td);
    fprintf(stderr, "%f\n%f\n%f\n",
        (tb.tv_sec - ta.tv_sec) + (tb.tv_nsec - ta.tv_nsec) * 0.000000001,
        (tc.tv_sec - tb.tv_sec) + (tc.tv_nsec - tb.tv_nsec) * 0.000000001,
        (td.tv_sec - tc.tv_sec) + (td.tv_nsec - tc.tv_nsec) * 0.000000001);
    #endif
}
