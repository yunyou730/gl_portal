
#include "../headers/AYYFrameBuffer.h"

namespace ayy {

AYYFrameBuffer::AYYFrameBuffer()
{
    Gen();
}

AYYFrameBuffer::~AYYFrameBuffer()
{
    Destroy();
}

void AYYFrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER,_fbo);
}

void AYYFrameBuffer::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void AYYFrameBuffer::Gen()
{
    int width = 800;
    int height = 600;
    
    // generate FBO
    glGenFramebuffers(1,&_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER,_fbo);
    
    
    // frame buffer 颜色缓冲
    // generate Texture saving color for FBO
    glGenTextures(1,&_texColoBuffer);
    glBindTexture(GL_TEXTURE_2D,_texColoBuffer);
    /*
     
     // Pass data from memory to GPU
     glTexImage2D(GL_TEXTURE_2D,0,
                  _saveFormat,
                  _raw->width,
                  _raw->height,
                  0,
                  _rawFormat,
                  GL_UNSIGNED_BYTE,
                  _raw->data);
     
     **/
    // @miao @temp 800 x 600
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 width,
                 height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 nullptr);
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // attach texture to current frame buffer
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,_texColoBuffer,0);
    
    
    
    // frame buffer 深度缓冲
    glGenRenderbuffers(1,&_rbo);
    glBindRenderbuffer(GL_RENDERBUFFER,_rbo);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,width,height);
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,_rbo);

    
    // 检查 fbo 是否 OK
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        assert(false);
    }
    
    // fbo 设置完毕，解除绑定
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void AYYFrameBuffer::Destroy()
{
    glDeleteRenderbuffers(1,&_rbo);
    glDeleteTextures(1,&_texColoBuffer);
    glDeleteFramebuffers(1,&_fbo);
}

}

