#ifndef GAMELIB_BASE_HPP
#define GAMELIB_BASE_HPP

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <czmq.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <hatchetfish.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <memory>
#include <thread>
#include <stdexcept>

namespace GameLib {
    struct SPRITEINFO {
        glm::vec2 position;
        float angle;
        glm::vec2 center;
        int flipFlags;
    };

    struct TILEIMAGE {
        SDL_Texture* texture{ nullptr };
        int tileId{ 0 };
        int tilesetId{ 0 };
        int w{ 0 };
        int h{ 0 };
    };

    struct AUDIOINFO {
        Mix_Chunk* chunk{ nullptr };
        std::string name;

        operator bool() const { return chunk != nullptr; }

        void free() {
            Mix_FreeChunk(chunk);
            chunk = nullptr;
        }

        ~AUDIOINFO() {
            if (chunk) {
                HFLOGERROR("Should not delete sound in destructor");
            }
        }
    };

    struct MUSICINFO {
        Mix_Music* chunk{ nullptr };
        std::string name;

        operator bool() const { return chunk != nullptr; }

        void free() {
            Mix_FreeMusic(chunk);
            chunk = nullptr;
        }

        ~MUSICINFO() {
            if (chunk) {
                HFLOGERROR("Should not delete sound in destructor");
            }
        }
    };

	template <typename T>
	T clamp(T x, T a, T b) {
        return (x < a) ? a : (x > b) ? b : x;
	}
}

#endif
