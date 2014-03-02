#include "Color.hpp"

Color::Color(BYTE R, BYTE G, BYTE B, BYTE A = 255)
{
	r = R;
	g = G;
	b = B;
	a = A;
}

extern "C"
{
	static VALUE color_Free(Color *colorObj)
	{
		delete colorObj;
		return Qnil;
	}

	static VALUE color_New(int argc, VALUE *argv, VALUE klass)
	{
		Color *color_obj;

		if (argc == 3) 
			color_obj = new Color(argv[0], argv[1], argv[2]);
		else
			color_obj = new Color(argv[0], argv[1], argv[2], argv[3]);

		VALUE newColor = Data_Wrap_Struct(klass, 0, color_Free, color_obj);

		rb_iv_set(newColor, "@r", argv[0]);
		rb_iv_set(newColor, "@g", argv[1]);
		rb_iv_set(newColor, "@b", argv[2]);
		rb_iv_set(newColor, "@a", argc == 3 ? 255 : argv[3]);

		return newColor;
	}

	static VALUE color_changeR(VALUE klass, VALUE R)
	{
		Color *color_obj;	
		Data_Get_Struct(klass, Color, color_obj);
		color_obj->r = NUM2INT(R);
		rb_iv_set(klass, "@r", R);
		return R;
	}

	static VALUE color_changeG(VALUE klass, VALUE G)
	{
		Color *color_obj;	
		Data_Get_Struct(klass, Color, color_obj);
		color_obj->g = NUM2INT(G);
		rb_iv_set(klass, "@g", G);
		return G;
	}

	static VALUE color_changeB(VALUE klass, VALUE B)
	{
		Color *color_obj;	
		Data_Get_Struct(klass, Color, color_obj);
		color_obj->b = NUM2INT(B);
		rb_iv_set(klass, "@b", B);
		return B;
	}

	static VALUE color_changeA(VALUE klass, VALUE A)
	{
		Color *color_obj;	
		Data_Get_Struct(klass, Color, color_obj);
		color_obj->a = NUM2INT(A);
		rb_iv_set(klass, "@a", A);
		return A;
	}
}

VALUE wrapColorClass(BYTE R, BYTE G, BYTE B, BYTE A = 255)
{
	Color *color_obj;
	color_obj = new Color(R, G, B, A);
	VALUE newColor = Data_Wrap_Struct(rb_path2class("RGA::Color"), 0, color_Free, color_obj);
	return newColor;
}

void defineEnumConst(VALUE klass)
{
	rb_define_const(klass, "Red",         wrapColorClass(255, 0, 0));
	rb_define_const(klass, "Green",       wrapColorClass(0, 255, 0));
	rb_define_const(klass, "Blue",        wrapColorClass(0, 0, 255));
	rb_define_const(klass, "Black",       wrapColorClass(0, 0, 0));
	rb_define_const(klass, "White",       wrapColorClass(255, 255, 255));
	rb_define_const(klass, "Transparent", wrapColorClass(0, 0, 0, 0));
}

void colorInit()
{
	VALUE newColor = rb_define_class_under(RGA, "Color", rb_cObject);
	rb_define_singleton_method(newColor, "new", (ruby_method*)&color_New, -1);
	rb_define_attr_method(newColor, "r", Qtrue, (ruby_method*)&color_changeR);
	rb_define_attr_method(newColor, "g", Qtrue, (ruby_method*)&color_changeG);
	rb_define_attr_method(newColor, "b", Qtrue, (ruby_method*)&color_changeB);
	rb_define_attr_method(newColor, "a", Qtrue, (ruby_method*)&color_changeA);
	defineEnumConst(newColor);
}