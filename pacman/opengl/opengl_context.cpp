#include <opengl/opengl_context.hpp>
#include <GL/glew.h>
#include <mathgl/mathgl.h>
#include <stdexcept>

namespace pacman {
    opengl_context::opengl_context():
      screen_size_(0,0),
      shader_program(0),
      attribute_coord2d(0),
      attribute_texcoord(0),
      uniform_texture(0),
      uniform_mvpmat(0) {
    }

    opengl_context::~opengl_context() {
        if(shader_program) {
            glDeleteProgram(shader_program);
        }
    }

    void opengl_context::initialize(size_in_pixels_t screen_size) {
        screen_size_ = screen_size;
        if(glewInit() != GLEW_OK) {
            throw std::runtime_error("glew error");
        }
        glPixelStorei(GL_PACK_ALIGNMENT,1);
        glClearColor(0.0f,0.0f,0.0f,0.0f);
        glViewport(0,0,screen_size_.width,screen_size_.height);
        uint32_t vertex_shader = create_shader(
            "#version 120\n"
            "uniform mat2 mvpmat;\n"
            "attribute vec2 coord2d;\n"
            "attribute vec2 texcoord;\n"
            "varying vec2 f_texcoord;\n"
            "void main(void) {\n"
            "    gl_Position = vec4(coord2d*mvpmat, 0.0, 1.0);\n"
            "    f_texcoord = texcoord;\n"
            "}\n",GL_VERTEX_SHADER);
        uint32_t fragment_shader = create_shader(
            "varying vec2 f_texcoord;\n"
            "uniform sampler2D mytexture;\n"
            "void main(void) {\n"
            "    vec2 flipped_texcoord = vec2(f_texcoord.x, 1.0 - f_texcoord.y);"
            "    gl_FragColor = texture2D(mytexture, flipped_texcoord);\n"
            "}\n",GL_FRAGMENT_SHADER);
        shader_program = glCreateProgram();
        if(shader_program == 0) {
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
            throw std::runtime_error("glCreateProgram error");
        }
        glAttachShader(shader_program,vertex_shader);
        glAttachShader(shader_program,fragment_shader);
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        glLinkProgram(shader_program);
        int status;
        glGetProgramiv(shader_program, GL_LINK_STATUS, &status);
        if(status != GL_TRUE) {
            throw std::runtime_error("glLinkProgram error");
        }
        glUseProgram(shader_program);
        attribute_coord2d = glGetAttribLocation(shader_program,"coord2d");
        if(attribute_coord2d == -1) {
            throw std::runtime_error("attribute_coord2d error");
        }
        attribute_texcoord = glGetAttribLocation(shader_program,"texcoord");
        if(attribute_texcoord == -1) {
            throw std::runtime_error("attribute_texcoord error");
        }
        uniform_texture = glGetUniformLocation(shader_program,"mytexture");
        if(uniform_texture == -1) {
            throw std::runtime_error("uniform_texture error");
        }
        uniform_mvpmat = glGetUniformLocation(shader_program,"mvpmat");
        if(uniform_mvpmat == -1) {
            throw std::runtime_error("uniform_projmat error");
        }
    }

    void opengl_context::render() {
        glClear(GL_COLOR_BUFFER_BIT);
        render_images();
    }

    void opengl_context::render_images() {
        for(auto temp_it = images_.begin();temp_it != images_.end();) {
            auto it = temp_it++;
            auto p_img = it->lock();
            if(p_img) {
                render_image(p_img);
            } else {
                images_.erase(it);
            }
        }
    }

    void opengl_context::render_image(const std::shared_ptr<opengl_image>& p_img) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,p_img->get_texture_id());
        glUniform1i(uniform_texture,0);
        float quad_texcoords[] = {
            0.f,0.f,
            1.f,0.f,
            0.f,1.f,
            1.f,0.f,
            0.f, 1.f,
            1.f,1.f
        };
        auto img_size = p_img->get_size();
        auto coords = p_img->get_coords();
        float triangles[] = {
            -screen_size_.width/2.f+coords.x,                  screen_size_.height/2.f - coords.y - img_size.height,
            -screen_size_.width/2.f+coords.x + img_size.width, screen_size_.height/2.f - coords.y - img_size.height,
            -screen_size_.width/2.f+coords.x,                  screen_size_.height/2.f - coords.y,
            -screen_size_.width/2.f+coords.x + img_size.width, screen_size_.height/2.f - coords.y - img_size.height,
            -screen_size_.width/2.f+coords.x,                  screen_size_.height/2.f - coords.y,
            -screen_size_.width/2.f+coords.x + img_size.width, screen_size_.height/2.f - coords.y
        };

        mat2 projection_mat(2.f/screen_size_.width,0,
            0,2.f/screen_size_.height);
        mat2 rotation_mat(cosf(p_img->get_rotation_angle()),-sinf(p_img->get_rotation_angle()),
            sinf(p_img->get_rotation_angle()),cosf(p_img->get_rotation_angle()));
        mat2 mvp_map = rotation_mat*projection_mat;
        glUniformMatrix2fv(uniform_mvpmat,1,GL_TRUE,mvp_map.m);
        glEnableVertexAttribArray(attribute_coord2d);
        glVertexAttribPointer(
            attribute_coord2d,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            triangles
            );
        glEnableVertexAttribArray(attribute_texcoord);
        glVertexAttribPointer(
            attribute_texcoord,
            2,
            GL_FLOAT,
            GL_FALSE,
            0,
            quad_texcoords
            );
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisableVertexAttribArray(attribute_coord2d);
        glDisableVertexAttribArray(attribute_texcoord);
    }

    std::shared_ptr<user_image> opengl_context::create_image() {
        auto p_image = std::make_shared<opengl_image>();
        images_.emplace_back(p_image);
        return p_image;
    }

    uint32_t opengl_context::create_shader(std::string src,uint32_t type) {
        uint32_t shader = glCreateShader(type);
        if(shader == 0) {
            throw std::runtime_error("glCreateShader error");
        }
        auto src_text = src.c_str();
        glShaderSource(shader,1,&src_text,NULL);
        glCompileShader(shader);
        int status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status != GL_TRUE) {
            glDeleteShader(shader);
            throw std::runtime_error("glCompileShader error");
        }
        return shader;
    }
}
