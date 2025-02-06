#pragma once

namespace rps::domain::interface
{

template <typename ContextType>
class Pipeline
{
public:
    class Pipe
    {
    public:
        virtual ~Pipe() = default;

        virtual void run(ContextType& context) = 0;
    };

    virtual ~Pipeline() = default;

    virtual void run(ContextType& context) = 0;
};

} // namespace rps::domain::interface
