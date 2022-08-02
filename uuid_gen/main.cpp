#include "id_generator_simple.h"
#include <sys/time.h>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        printf("%s name loop_num [file_name]\n", argv[0]);
        return -1;
    }

    int ret = 0;

    int n = atol(argv[2]);

    int64_t* r = new int64_t[n];

    int f = 0;

    CIdGeneratorSimple idWorker(argv[1]);

    struct timeval b;
    gettimeofday(&b, NULL);

    for (int i = 0; i < n; i++)
    {
        ret = idWorker.GetNextId(r[i]);
        if(0 != ret)
        {
            ++f;
        }
    }

    struct timeval e;
    gettimeofday(&e, NULL);

    printf("fail=%d, use_us=%jd\n", f, (int64_t)e.tv_sec*1000000 - (int64_t)b.tv_sec*1000000 + (e.tv_usec - b.tv_usec));

    if(argc >= 4)
    {
        ofstream os(argv[3], ios::trunc);
        for (int i = 0; i < n; i++)
        {
            os << r[i] << endl;
        }
    }

    return 0;
}
