#pragma once
#include <string>
#include <memory>
#include <vector>
#include <stdexcept>

namespace Engine
{

    struct Sound
    {
        int id;
        std::string filePath;
        std::unique_ptr<char[]> data;
        size_t dataSize;

        Sound() : id(-1), dataSize(0) {}
    };

    class Audio
    {
    public:
        Audio();
        ~Audio();

        void PlaySound(int soundId);
        void PlaySound(const Sound& sound);
        Sound FromWav(const std::string& filePath);

        bool UnloadSound(int soundId);
        const std::vector<Sound>& GetLoadedSounds() const;
        void ClearAllSounds();

    private:
        int nextSoundId;
        std::vector<Sound> loadedSounds;

        int FindSoundIndex(int soundId) const;
    };
}
