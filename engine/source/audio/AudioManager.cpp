#include"audio/AudioManager.h"
#include <glm/glm.hpp>  
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

namespace eng
{
    AudioManager::AudioManager()
    {
        m_engine = std::make_unique<ma_engine>();
    }
    AudioManager::~AudioManager()
    {
        if (m_engine)
        {
            ma_engine_uninit(m_engine.get());
        }
    }
    bool AudioManager::Init()
    {
        auto result = ma_engine_init(nullptr, m_engine.get());
        return result == MA_SUCCESS;
    }
    ma_engine* AudioManager::GetEngine()
    {
        return m_engine.get();
    }
    void AudioManager::SetListenerPosition(const glm::vec3& position)
    {
        if (m_engine)
        {
            ma_engine_listener_set_position(m_engine.get(), 0, position.x, position.y, position.z);
        }
    }
}