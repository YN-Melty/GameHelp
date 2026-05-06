#include "Managers/AudioManager.h"

#include <SFML/Audio/Listener.hpp>

void AudioManager::SetGlobalVolume(float volume)
{
    sf::Listener::setGlobalVolume(volume);
}

float AudioManager::GetGlobalVolume() const
{
    return sf::Listener::getGlobalVolume();
}

sf::Vector3f AudioManager::GetListenerPosition() const
{
    return sf::Listener::getPosition();
}