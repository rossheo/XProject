#include "stdafx.h"
#include "random_engine.h"

namespace XP
{

RandomEngine::RandomEngine()
{
    std::random_device randomDevice;
    _randomEngine.seed(randomDevice());
}

RandomEngine::~RandomEngine()
{
}

} // namespace XP