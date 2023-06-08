#include "ya2d++.h"
#include <string>
#include <common.h>

Image::Image(){
    this->is_system_image = false;
}

Image::Image(ya2d_texture* tex){
    this->texture = tex;
    this->is_system_image = false;
    flush();
}

Image::Image(string filename, int place){
    this->is_system_image = false;
    string ext = common::getExtension(filename);
    if (ext == "png"){
        this->texture = ya2d_load_PNG_file_offset(filename.c_str(), place, 0);
    }
    else if (ext == "jpg" || ext == "jpeg"){
        this->texture = ya2d_load_JPEG_file(filename.c_str(), place);
    }
    else if (ext == "bmp"){
        this->texture = ya2d_load_BMP_file(filename.c_str(), place);
    }
    flush();
}

Image::Image(void* buffer, int place){
    this->is_system_image = false;
    u32 magic = *(u32*)buffer;
    if (magic == PNG_MAGIC)
        this->texture = ya2d_load_PNG_buffer(buffer, place);
    else if (magic == BMP_MAGIC)
        this->texture = ya2d_load_BMP_buffer(buffer, place);
    flush();
}

Image::Image(void* buffer, unsigned long buffer_size, int place){
    this->is_system_image = false;
    if ( (*(u32*)buffer & 0x0000FFFF) == JPG_MAGIC)
        this->texture = ya2d_load_JPEG_buffer(buffer, buffer_size, place);
    flush();
}

Image::Image(string filename, int place, SceOff offset){
    this->is_system_image = false;
    this->texture = ya2d_load_PNG_file_offset(filename.c_str(), place, offset);
    flush();
}

Image::~Image(){
    ya2d_free_texture(this->texture);
}

ya2d_texture* Image::getTexture(){
    return this->texture;
}

int Image::getWidth(){
    return this->texture->width;
}

int Image::getHeight(){
    return this->texture->height;
}

void Image::swizzle(){
    ya2d_swizzle_texture(this->texture);
    flush();
}

void Image::flush(){
    ya2d_flush_texture(this->texture);
}

void Image::draw(int x, int y){
    ya2d_draw_texture(this->texture, x, y);
}

void Image::draw_centered(int x, int y){
    ya2d_draw_texture_centered(this->texture, x, y);
}

void Image::draw_hotspot(int x, int y, int center_x, int center_y){
    ya2d_draw_texture_hotspot(this->texture, x, y, center_x, center_y);
}

void Image::draw_scale(int x, int y, float scale_x, float scale_y){
    ya2d_draw_texture_scale(this->texture, x, y, scale_x, scale_y);
}

void Image::draw_scale(int x, int y, int newWidth, int newHeight){
    float scale_x = (float)newWidth/(float)this->texture->width;
    float scale_y = (float)newHeight/(float)this->texture->height;
    ya2d_draw_texture_scale(this->texture, x, y, scale_x, scale_y);
}

void Image::draw_rotate(int x, int y, float angle){
    ya2d_draw_texture_rotate(this->texture, x+texture->width/2, y+texture->height/2, angle);
}

void Image::draw_rotate_hotspot(int x, int y, float angle, int center_x, int center_y){
    ya2d_draw_texture_rotate_hotspot(this->texture, x, y, angle, center_x, center_y);
}

bool Image::operator==(Image* other){
    return ((u32)this == (u32)other) || (this->texture == other->texture);
}
