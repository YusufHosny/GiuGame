#ifndef IDGENERATOR_H
#define IDGENERATOR_H

class IdGenerator
{
    public:
        IdGenerator() = delete;

        static int generateId();


    private:
        static unsigned int nextId;
};

#endif // IDGENERATOR_H
