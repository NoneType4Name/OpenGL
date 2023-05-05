#include <tuple>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#ifdef _WIN32
    #include <windows.h>
    #include <WinUser.h>
    #include <windowsx.h>
    std::tuple<uint16_t, uint16_t> GetFullSize(){
        DEVMODE dMode;
        EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dMode);
        return std::tuple<uint16_t, uint16_t>{dMode.dmPelsWidth, dMode.dmPelsHeight};
    }
    uint32_t GetShader(std::string path, GLenum shader_type, uint32_t count){
        std::ifstream shader(path);
        if (shader.is_open()){
            std::stringstream steamstring_of_shader;
            steamstring_of_shader << shader.rdbuf();
            shader.close();
            const std::string StringSourceShader{steamstring_of_shader.str()};
            const GLchar *SourceShader = &StringSourceShader.c_str()[0];
            GLint status;
            uint32_t ShaderNum{glCreateShader(shader_type)};
            glShaderSource(ShaderNum, count, &SourceShader, NULL);
            glCompileShader(ShaderNum);
            glGetShaderiv(ShaderNum, GL_COMPILE_STATUS, &status);
            if (!status){
                GLint len;
                glGetShaderiv(ShaderNum, GL_INFO_LOG_LENGTH, &len);
                GLchar info[len];
                glGetShaderInfoLog(ShaderNum, len, NULL, info);
                std::cout << "ERROR COMIPE SHADER FROM PATH " << path << "\nlog:\n" << info << std::endl;
                getchar();
            }
            return ShaderNum;
        }
        else{
            std::cout << "Error load path " << path << std::endl;
            getchar();
        }
        return -1;
    }
    GLuint LinkAndDelShaders(std::vector<uint32_t>shaders){
        GLuint sProgram{glCreateProgram()};
        GLint status;
        for(uint32_t s: shaders){
            glAttachShader(sProgram, s);
            glDeleteShader(s);
            }
        glLinkProgram(sProgram);
        glGetProgramiv(sProgram, GL_LINK_STATUS, &status);
        if (!status){
            GLint len;
            glGetProgramiv(sProgram, GL_INFO_LOG_LENGTH, &len);
            GLchar info[len];
            glGetProgramInfoLog(sProgram, len, NULL, info);
            std::cout << "ERROR LINK SHADERS\nlog:\n" << info << std::endl;
            getchar();
        }
        return sProgram;

    }
#endif