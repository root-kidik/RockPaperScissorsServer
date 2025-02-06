#pragma once

#include <memory>
#include <vector>

namespace rps::domain::util
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

    template <typename Pipe, typename... Args>
    void add(Args&&... args)
    {
        m_pipes.emplace_back(std::make_unique<Pipe>(std::forward<Args>(args)...));
    }

    void run(ContextType& context)
    {
        for (auto& pipe : m_pipes)
            pipe->run(context);
    }

private:
    std::vector<std::unique_ptr<Pipe>> m_pipes;
};

} // namespace rps::domain::util
