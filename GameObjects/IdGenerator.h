#ifndef IDGENERATOR_HPP
#define IDGENERATOR_HPP

class IdGenerator
{
    public:
        IdGenerator() = delete;

        static int generateId();


    private:
        static unsigned int nextId;
};

#endif // IDGENERATOR_HPP
