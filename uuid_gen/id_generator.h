/// @file id_generator.h
/// @brief
/// @author samzou samzou@tencent.com
/// @version 1.0
/// @date 2017-02-18
/// @copyright Copyright (c) 2017 Tencent Inc. All Rights Reserved.
#pragma once


#include <stdint.h>

#include <string>

class CIdGenerator
{
enum EIdGeneratorCode
{
    E_ID_GENERATOR_CODE_SUCC = 0,
    E_ID_GENERATOR_CODE_SHM = -463701,
    E_ID_GENERATOR_CODE_TIME = -463702,
    E_ID_GENERATOR_CODE_WORKER_ID = -463703,
    E_ID_GENERATOR_CODE_SEQ = -463704,
};

public:
    explicit CIdGenerator(const std::string& name);

    virtual ~CIdGenerator()
    {
        Detach();
    }

public:
    int GetNextId(int64_t& id);

    static int64_t DecodeTime(int64_t id);

protected:
    int InitShm();
    int BuildShm();

    int Detach();

    virtual int GetTime(int64_t& timestamp);

    virtual int GetWorkerId(int64_t& worker_id);

    virtual int GetSequence(int64_t& sequence, int64_t& timestamp);

    void ThreadLock();

    void ThreadUnLock();

protected:
    virtual int GetWorkerIdImp(int64_t& worker_id) = 0;

protected:
    int64_t _worker_id_bits;
    int64_t _max_worker_id;
    int64_t _sequence_bits;
    int64_t _sequence_mask;
    int64_t _max_sequenc;
    int64_t _worker_id_shift;
    int64_t _timestamp_shift;

    int64_t _shm_sequence_mask;
    int64_t _shm_begin_sequence_mask;

    int64_t _last_timestamp;

    std::string _name;

    std::string _shm_name;
    void *_shm_p;
    int _shm_fd;
    bool _shm_init;

};


