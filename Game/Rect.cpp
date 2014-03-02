#include "Rect.hpp"

Rect::Rect(unsigned int left, unsigned int top, unsigned int width, unsigned int height)
{
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;	
}

bool Rect::intersects(unsigned x, unsigned width, unsigned int x2, unsigned int width2)
{
	if ((x + width >= x2) && (x <= x2 + width2))
		return true;

	return false;
}

extern "C"
{
	static VALUE rect_Free(Rect *rectObj)
	{
		delete rectObj;
		return Qnil;
	}

	static VALUE rect_New(VALUE klass, VALUE left, VALUE top, VALUE width, VALUE height)
	{
		Rect *rect_obj = new Rect(NUM2UINT(left), NUM2UINT(top), NUM2UINT(width), NUM2UINT(height));
		VALUE newRect = Data_Wrap_Struct(klass, 0, rect_Free, rect_obj);

		rb_iv_set(newRect, "@left",   left);
		rb_iv_set(newRect, "@top",    top);
		rb_iv_set(newRect, "@width",  width);
		rb_iv_set(newRect, "@height", height);

		return newRect;
	}

	static VALUE rect_changeLeft(VALUE klass, VALUE left)
	{
		Rect *rect_obj;	
		Data_Get_Struct(klass, Rect, rect_obj);
		rect_obj->left = NUM2UINT(left);
		rb_iv_set(klass, "@left", left);
		return Qnil;
	}

	static VALUE rect_changeTop(VALUE klass, VALUE top)
	{
		Rect *rect_obj;	
		Data_Get_Struct(klass, Rect, rect_obj);
		rect_obj->top = NUM2UINT(top);
		rb_iv_set(klass, "@top", top);
		return Qnil;
	}

	static VALUE rect_changeWidth(VALUE klass, VALUE width)
	{
		Rect *rect_obj;	
		Data_Get_Struct(klass, Rect, rect_obj);
		rect_obj->width = NUM2UINT(width);
		rb_iv_set(klass, "@width", width);
		return Qnil;
	}

	static VALUE rect_changeHeight(VALUE klass, VALUE height)
	{
		Rect *rect_obj;	
		Data_Get_Struct(klass, Rect, rect_obj);
		rect_obj->height = NUM2UINT(height);
		rb_iv_set(klass, "@height", height);
		return Qnil;
	}

	static VALUE rect_intersect(VALUE klass, VALUE rect)
	{
		Rect *rect_obj;	
		Data_Get_Struct(rect, Rect, rect_obj);
		bool intersect = Rect::intersects(rect_obj->left, rect_obj->top, rect_obj->width, rect_obj->height);
		return intersect ? Qtrue : Qfalse;
	}
}

void rectInit()
{
	VALUE newRect = rb_define_class_under(RGA, "Rect", rb_cObject);
	rb_define_singleton_method(newRect, "new", (ruby_method*)&rect_New, 4);
	rb_define_singleton_method(newRect, "intersect", (ruby_method*)&rect_intersect, 1);
	rb_define_attr_method(newRect, "left",    Qtrue, (ruby_method*)&rect_changeLeft);
	rb_define_attr_method(newRect, "top",     Qtrue, (ruby_method*)&rect_changeTop);
	rb_define_attr_method(newRect, "width",   Qtrue, (ruby_method*)&rect_changeWidth);
	rb_define_attr_method(newRect, "height",  Qtrue, (ruby_method*)&rect_changeHeight);
}