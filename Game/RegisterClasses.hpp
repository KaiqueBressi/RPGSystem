#ifndef REGISTER_H
#define REGISTER_H

#include "ruby.h"
#include "Sprite.hpp"
#include "RegisterClasses.hpp"
#include "Image.hpp"
#include "GraphicsModule.hpp"
#include "Color.hpp"

extern VALUE RGA;
typedef VALUE (ruby_method)(...);

void registerClasses();
void rb_define_attr_method(VALUE klass, std::string name, VALUE Readable, VALUE(*func)(...));
void rb_define_attr_method(VALUE klass, std::string name, VALUE (*readfunc)(...), VALUE(*func)(...));
#endif