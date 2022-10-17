#include "id_generator.h"

class CIdGeneratorSimple : public CIdGenerator
{
public:
    explicit CIdGeneratorSimple(const std::string& name) :
        CIdGenerator(name)
    {
    }

    virtual ~CIdGeneratorSimple()
    {
    }

    virtual int GetWorkerIdImp(int64_t& worker_id)
    {
        worker_id = 0;
        return 0;
    }
};
