#pragma once

#include <string>
#include <soloud_wav.h>
#include <plugin/Audio.h>
#include <resource/BinaryResource.h>
#include "TransformComponent.h"

namespace chira {

struct AudioWavComponent {
    static constexpr auto in_place_delete = true;

    explicit AudioWavComponent(const std::string& wavId) {
        this->wavFile = Resource::getResource<BinaryResource>(wavId);
        this->wav.loadMem(const_cast<unsigned char*>(this->wavFile->getBuffer()), static_cast<unsigned int>(this->wavFile->getBufferLength()), false, false);
    }

public:
    TransformComponent* transform = nullptr;
    SharedPointer<BinaryResource> wavFile;
    SoLoud::Wav wav;
};

} // namespace chira
