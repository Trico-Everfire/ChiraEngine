#pragma once

#include <string>
#include <soloud_wavstream.h>
#include <plugin/Audio.h>
#include <resource/BinaryResource.h>
#include "TransformComponent.h"

namespace chira {

struct AudioWavStreamComponent {
    static constexpr auto in_place_delete = true;

    explicit AudioWavStreamComponent(const std::string& wavStreamId) {
        this->wavFile = Resource::getResource<BinaryResource>(wavStreamId);
        this->wavStream.loadMem(const_cast<unsigned char*>(this->wavFile->getBuffer()), static_cast<unsigned int>(this->wavFile->getBufferLength()), false, false);
    }

public:
    TransformComponent* transform = nullptr;
    SharedPointer<BinaryResource> wavFile;
    SoLoud::WavStream wavStream;
};

} // namespace chira
