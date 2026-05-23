#include <Engine/Audio/Audio.h>
#include <fstream>
#include <stdexcept>

namespace Engine
{
    Audio::Audio() : nextSoundId(0)
    {
        // Initialization without console output
    }

    Audio::~Audio()
    {
        ClearAllSounds(); // Ensure all sounds are properly unloaded
    }

    void Audio::PlaySound(int soundId)
    {
        int index = FindSoundIndex(soundId);
        if (index == -1)
        {
            throw std::runtime_error("Sound with ID " + std::to_string(soundId) + " not found");
        }
        // In a real engine: audioBackend->Play(loadedSounds[index]);
    }

    void Audio::PlaySound(const Sound& sound)
    {
        if (sound.id == -1 || sound.dataSize == 0)
        {
            throw std::runtime_error("Cannot play invalid or unloaded sound");
        }
        // In a real engine: audioBackend->Play(sound);
    }

    Sound Audio::FromWav(const std::string& filePath)
    {
        Sound sound;
        sound.filePath = filePath;
        sound.id = nextSoundId++;

        std::ifstream file(filePath, std::ios::binary);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open WAV file: " + filePath);
        }

        char header[44];
        if (!file.read(header, 44))
        {
            throw std::runtime_error("Failed to read WAV header");
        }

        sound.dataSize = *reinterpret_cast<uint32_t*>(&header[40]);
        sound.data = std::make_unique<char[]>(sound.dataSize);

        if (!file.read(sound.data.get(), sound.dataSize))
        {
            throw std::runtime_error("Failed to read audio data");
        }

        file.close();
        loadedSounds.push_back(std::move(sound)); // Add to the list of loaded sounds
        return sound;
    }

    int Audio::FindSoundIndex(int soundId) const
    {
        for (size_t i = 0; i < loadedSounds.size(); ++i)
        {
            if (loadedSounds[i].id == soundId)
            {
                return static_cast<int>(i);
            }
        }
        return -1; // Not found
    }

    bool Audio::UnloadSound(int soundId)
    {
        int index = FindSoundIndex(soundId);
        if (index == -1)
        {
            throw std::runtime_error("Sound with ID " + std::to_string(soundId) + " not found");
        }

        loadedSounds.erase(loadedSounds.begin() + index);
        return true;
    }

    const std::vector<Sound>& Audio::GetLoadedSounds() const
    {
        return loadedSounds;
    }

    void Audio::ClearAllSounds()
    {
        loadedSounds.clear();
    }
}
