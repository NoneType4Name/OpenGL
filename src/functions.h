#include <tuple>
#ifdef _WIN32
    #include <windows.h>
    #include <fstream>
    std::tuple<uint16_t, uint16_t> GetFullSize(){
        return std::tuple<uint16_t, uint16_t>{GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)};
    }
    uint8_t[] GetShader(uint8_t path[]){
        uint8_t string_of_shader[];
        std::ifstream shader(path);
        if (shader.is_open()){
            shader >> string_of_shader;
        }
        return shader;
    }
#endif