#pragma once

#include <gmock/gmock.h>

#include <domain/model/Room.hpp>

using namespace rps;

class RoundPipelineMock final : public domain::model::Room::RoundPipeline
{
public:
    MOCK_METHOD(void, run, (domain::model::Room::RoundContext & context), (override));
};
