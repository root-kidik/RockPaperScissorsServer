#pragma once

#include <memory>
#include <vector>

#include <domain/interface/Pipeline.hpp>

namespace rps::domain::util
{

template <typename ContextType>
class Pipeline : public interface::Pipeline<ContextType>
{
public:
    template <typename Pipe, typename... Args>
    void add(Args&&... args)
    {
        m_pipes.emplace_back(std::make_unique<Pipe>(std::forward<Args>(args)...));
    }

    void run(ContextType& context) override
    {
        for (auto& pipe : m_pipes)
            pipe->run(context);
    }

private:
    std::vector<std::unique_ptr<typename interface::Pipeline<ContextType>::Pipe>> m_pipes;
};

} // namespace rps::domain::util
