#include "RegisterClasses.hpp"

VALUE RGA = Qnil;

void registerClasses()
{
	RGA = rb_define_module("RGA");
	graphicsInit();
	spriteInit();
	bitmapInit();
	rectInit();
	colorInit();
}

void rb_define_attr_method(VALUE klass, std::string name, VALUE Readable, VALUE(*func)(...))
{
	rb_define_attr(klass, name.c_str(), Readable, 1);
	rb_define_method(klass, (name + "=").c_str(), func, 1);
}

void rb_define_attr_method(VALUE klass, std::string name, VALUE (*readfunc)(...), VALUE(*func)(...))
{
	rb_define_attr(klass, name.c_str(), 1, 1); 
	rb_define_method(klass, (name + "=").c_str(), func, 1);
	rb_define_method(klass, name.c_str(), readfunc, 0);
}
