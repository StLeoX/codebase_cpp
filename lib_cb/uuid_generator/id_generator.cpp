#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/syscall.h>

#include <cstring>

#include "CAS_64bit.h"

#include "id_generator.h"

#define TIMESTAMP_OFFSET 910753871111LL
#define WORKER_ID_BITS 10LL
#define SEQUENCE_BITS 12LL
#define WORKER_ID_SHIFT SEQUENCE_BITS
#define TIMESTAMP_SHIFT (WORKER_ID_BITS + SEQUENCE_BITS)

#define SHM_BEGIN_SEQUENCE_BITS 10LL
#define SHM_SEQUENCE_BITS 13LL
#define SHM_BEGIN_SEQUENCE_SHIFT SHM_SEQUENCE_BITS
#define SHM_TIMESTAMP_SHIFT (SHM_BEGIN_SEQUENCE_BITS + SHM_SEQUENCE_BITS)

#define USE_BEGIN_SEQUENCE
//#define USE_CLOCK_MOVED_BACKWARDS

static int g_iIdGeneratorThreadLock = 0;

#pragma pack (1)
struct SIdGeneratorShm
{
    uint64_t seq;
    uint8_t ext[4088];
};
#pragma pack ()

CIdGenerator::CIdGenerator(const std::string& name) :
    _name(name),
    _shm_name("seqshm_" + name),
    _shm_p(NULL),
    _shm_fd(-1),
    _shm_init(false)
{
    _worker_id_bits = WORKER_ID_BITS;//10LL;
    _max_worker_id = -1LL ^ (-1LL << _worker_id_bits);

    _sequence_bits = SEQUENCE_BITS;//12LL;
    _sequence_mask = -1LL ^ (-1LL << _sequence_bits);
    _max_sequenc = -1LL ^ (-1LL << _sequence_bits);

    _worker_id_shift = WORKER_ID_SHIFT;//_sequence_bits;
    _timestamp_shift = TIMESTAMP_SHIFT;//_sequence_bits + _worker_id_bits;

    _shm_sequence_mask = -1LL ^ (-1LL << SHM_SEQUENCE_BITS);
    _shm_begin_sequence_mask = -1LL ^ (-1LL << SHM_BEGIN_SEQUENCE_BITS);

    _last_timestamp = TIMESTAMP_OFFSET;
}

int CIdGenerator::GetNextId(int64_t& id)
{
    int ret = 0;

    ret = InitShm();
    if(0 != ret)
    {
        return ret;
    }

    int64_t timestamp = 0;
    ret = GetTime(timestamp);
    if(0 != ret)
    {
        return ret;
    }

    int64_t worker_id = -1;
    ret = GetWorkerId(worker_id);
    if(0 != ret)
    {
        return ret;
    }

    int64_t sequence = 0;
    ret = GetSequence(sequence, timestamp);
    if(0 != ret)
    {
        return ret;
    }

    // 0       00000000000000000000000000000000000000000  0000000000  000000000000
    // 符号位  time                                       worker_id   sequence
    id = (timestamp << _timestamp_shift) | (worker_id << _worker_id_shift) | sequence;

    return 0;
}

int CIdGenerator::GetTime(int64_t& timestamp)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    int64_t ts = (int64_t)tv.tv_sec*1000 + tv.tv_usec/1000;
    if(ts < _last_timestamp)
    {
#ifdef USE_CLOCK_MOVED_BACKWARDS
        return E_ID_GENERATOR_CODE_TIME;
#else
        ts = _last_timestamp;
#endif
    }

    _last_timestamp = ts;
    timestamp = ts - TIMESTAMP_OFFSET;

    return 0;
}

int CIdGenerator::GetWorkerId(int64_t& worker_id)
{
    int ret = 0;

    int64_t wid = -1;

    ret = GetWorkerIdImp(wid);
    if(0 != ret)
    {
        return ret;
    }

    if(wid > _max_worker_id || wid < 0)
    {
        return E_ID_GENERATOR_CODE_WORKER_ID;
    }

    worker_id = wid;

    return 0;
}

int CIdGenerator::GetSequence(int64_t& sequence, int64_t& timestamp)
{
    uint64_t seq = 0;
    int64_t shm_ts = 0;

    uint64_t shm_seq = 0;
    uint64_t shm_begin_seq = 0;

    for(;;)
    {
        uint64_t old_seq = ((SIdGeneratorShm*)_shm_p)->seq;

        shm_ts = old_seq >> SHM_TIMESTAMP_SHIFT;

        if(timestamp > shm_ts)
        {
            uint64_t ts = timestamp;
            for(;;)
            {
                // 使用begin_seq，避免生成最小位是0、1比较多，对hash不友好
                // 00000000000000000000000000000000000000000  0000000000  0000000000000
                // time                                       begin_seq   sequence
#ifdef USE_BEGIN_SEQUENCE
                uint64_t begin_seq = old_seq & _shm_begin_sequence_mask;
#else
                uint64_t begin_seq = 0;
#endif
                uint64_t new_seq = (ts << SHM_TIMESTAMP_SHIFT) | (begin_seq << SHM_BEGIN_SEQUENCE_SHIFT) | begin_seq;
                if(CAS_64bit(&((SIdGeneratorShm*)_shm_p)->seq, old_seq, new_seq))
                {
                    old_seq = new_seq;
                    shm_ts = ts;
                    break;
                }
                else
                {
                    old_seq = ((SIdGeneratorShm*)_shm_p)->seq;
                    shm_ts = old_seq >> SHM_TIMESTAMP_SHIFT;
                    if(timestamp <= shm_ts)
                    {
                        break;
                    }
                }
            }
        }

        shm_seq = old_seq & _shm_sequence_mask;
        shm_begin_seq = (old_seq >> SHM_BEGIN_SEQUENCE_SHIFT) & _shm_begin_sequence_mask;
        if(shm_seq >= shm_begin_seq + _max_sequenc)
        {
            return E_ID_GENERATOR_CODE_SEQ;
        }

        seq = old_seq + 1;

        if(CAS_64bit(&((SIdGeneratorShm*)_shm_p)->seq, old_seq, seq))
        {
            break;
        }
    }

    sequence = seq & _sequence_mask;

    if(timestamp > shm_ts)
    {
        return E_ID_GENERATOR_CODE_SEQ;
    }

    timestamp = shm_ts;

    return 0;
}

int64_t CIdGenerator::DecodeTime(int64_t id)
{
    return (id >> TIMESTAMP_SHIFT) + TIMESTAMP_OFFSET;
}

int CIdGenerator::InitShm()
{
    if(_shm_init)
    {
        return 0;
    }

    ThreadLock();

    if(_shm_init)
    {
        ThreadUnLock();
        return 0;
    }

    int ret = 0;

    ret = BuildShm();
    if(0 != ret)
    {
        ThreadUnLock();
        return ret;
    }

    _shm_init = true;

    ThreadUnLock();

    return 0;
}

int CIdGenerator::BuildShm()
{
    size_t size = sizeof(SIdGeneratorShm);

    int fd = shm_open(_shm_name.c_str(), O_RDWR, 0777);
    if(0 > fd)
    {
        char shm_name_temp[256];
        snprintf(shm_name_temp, sizeof(shm_name_temp), "%s.%ld", _shm_name.c_str(), syscall(SYS_gettid));

        char path_old[256] = {0};
        char path_new[256] = {0};
        snprintf(path_old, sizeof(path_old), "/dev/shm/%s", shm_name_temp);
        snprintf(path_new, sizeof(path_new), "/dev/shm/%s", _shm_name.c_str());

        unlink(path_old);

        fd = shm_open(shm_name_temp, O_CREAT | O_RDWR, 0777);
        if(0 > fd)
        {
            return E_ID_GENERATOR_CODE_SHM;
        }

        int ret = ftruncate(fd, size);
        if(0 > ret)
        {
            close(fd);
            return E_ID_GENERATOR_CODE_SHM;
        }

        void* addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, SEEK_SET);
        if(NULL == addr)
        {
            close(fd);
            return E_ID_GENERATOR_CODE_SHM;
        }

        memset(addr, 0, size);

        munmap(addr, size);

        close(fd);

        link(path_old, path_new);

        unlink(path_old);

        fd = shm_open(_shm_name.c_str(), O_RDWR, 0777);
        if(0 > fd)
        {
            return E_ID_GENERATOR_CODE_SHM;
        }
    }

    void* addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, SEEK_SET);
    if(NULL == addr)
    {
        close(fd);
        return E_ID_GENERATOR_CODE_SHM;
    }

    _shm_p = addr;
    _shm_fd = fd;

    return 0;
}

int CIdGenerator::Detach()
{
    int ret = 0;
    if(_shm_p != NULL)
    {
        munmap(_shm_p, sizeof(SIdGeneratorShm));

        _shm_p = NULL;
    }

    if(_shm_fd >= 0)
    {
        close(_shm_fd);

        _shm_fd = -1;
    }

    return ret;
}

void CIdGenerator::ThreadLock()
{
    while(__sync_lock_test_and_set(&g_iIdGeneratorThreadLock, 1)) {}
}

void CIdGenerator::ThreadUnLock()
{
    __sync_lock_release(&g_iIdGeneratorThreadLock);
}

