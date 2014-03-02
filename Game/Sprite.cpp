#include "Sprite.hpp"

std::vector<SpriteClass*> spriteVector;

SpriteClass::SpriteClass()
{
	spriteVector.push_back(this);
	visible = true;
}

SpriteClass::~SpriteClass()
{
	dispose();
}

void SpriteClass::dispose()
{
	for (unsigned int i = 0; i < spriteVector.size(); i++)
	{	
		if (spriteVector[i] == this)
			spriteVector.erase((spriteVector.begin() + i));
	}
}

void SpriteClass::loadFromFile(char * filename) 
{
	tTexture.loadFromFile(filename);
	tSprite.setTexture(tTexture);
}

void SpriteClass::changeImage(Bitmap image)
{
	tTexture = image.getTexture();
	tSprite.setTexture(tTexture);
}

void SpriteClass::setVisible(bool visible)
{
	this->visible = visible;
}

extern "C"
{
	Bitmap *cloneBitmap = new Bitmap(1, 1);

	static VALUE sprite_Free(SpriteClass *spriteObj)
	{
		delete spriteObj;
		return Qnil;
	}

	static VALUE bitmap_Free(Bitmap *imageObj)
	{
		delete imageObj;
		return Qnil;
	} 

	static VALUE sprite_New(VALUE klass)
	{
		SpriteClass *spriteObj = new SpriteClass();
		VALUE newSprite = Data_Wrap_Struct(klass, 0, sprite_Free, spriteObj);
		
		rb_iv_set(newSprite, "@x",        INT2NUM(0));
		rb_iv_set(newSprite, "@y",        INT2NUM(0));
		rb_iv_set(newSprite, "@left",     INT2NUM(0));
		rb_iv_set(newSprite, "@top",      INT2NUM(0));
		rb_iv_set(newSprite, "@width",    INT2NUM(0));
		rb_iv_set(newSprite, "@height",   INT2NUM(0));
		rb_iv_set(newSprite, "@rotation", INT2NUM(0));
		rb_iv_set(newSprite, "@opacity",  INT2NUM(255));
		rb_iv_set(newSprite, "@bitmap",   Qnil);
		rb_iv_set(newSprite, "@visible",  Qtrue);

		return newSprite;
	}

	static VALUE sprite_Dispose(VALUE klass)
	{
		SpriteClass *spriteClass_obj;	
		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		spriteClass_obj->dispose();
		return Qnil;
	}

	static VALUE sprite_changeX(VALUE klass, VALUE x)
	{
		SpriteClass *spriteClass_obj;	
		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		spriteClass_obj->tSprite.setPosition(NUM2DBL(x), spriteClass_obj->tSprite.getPosition().y);
		rb_iv_set(klass, "@x", x);
		return Qnil;
	}

	static VALUE sprite_changeY(VALUE klass, VALUE y)
	{
		SpriteClass *spriteClass_obj;	
		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		spriteClass_obj->tSprite.setPosition(spriteClass_obj->tSprite.getPosition().x, NUM2DBL(y));
		rb_iv_set(klass, "@y", y);
		return Qnil;
	}

	static VALUE sprite_changeWidth(VALUE klass, VALUE width)
	{
		SpriteClass *spriteClass_obj;	
		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		sf::IntRect rect = spriteClass_obj->tSprite.getTextureRect();
		spriteClass_obj->tSprite.setTextureRect(sf::IntRect(rect.left, rect.top, NUM2DBL(width), rect.height));
		rb_iv_set(klass, "@width", width);
		return Qnil;
	}

	static VALUE sprite_changeHeight(VALUE klass, VALUE height)
	{
		SpriteClass *spriteClass_obj;	
		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		sf::IntRect rect = spriteClass_obj->tSprite.getTextureRect();
		spriteClass_obj->tSprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, NUM2DBL(height)));
		rb_iv_set(klass, "@height", height);
		return Qnil;
	}

	static VALUE sprite_changeLeft(VALUE klass, VALUE left)
	{
		SpriteClass *spriteClass_obj;	
		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		sf::IntRect rect = spriteClass_obj->tSprite.getTextureRect();
		spriteClass_obj->tSprite.setTextureRect(sf::IntRect(NUM2DBL(left), rect.top, rect.width, rect.height));
		rb_iv_set(klass, "@left", left);
		return Qnil;
	}

	static VALUE sprite_changeTop(VALUE klass, VALUE top)
	{
		SpriteClass *spriteClass_obj;	
		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		sf::IntRect rect = spriteClass_obj->tSprite.getTextureRect();
		spriteClass_obj->tSprite.setTextureRect(sf::IntRect(rect.left, NUM2DBL(top), rect.width, rect.height));
		rb_iv_set(klass, "@top", top);
		return Qnil;
	}

	static VALUE sprite_changeRect(VALUE klass, VALUE rect)
	{
		SpriteClass *spriteClass_obj;
		Rect *rect_obj;

		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		Data_Get_Struct(rect, Rect, rect_obj);

		spriteClass_obj->tSprite.setTextureRect(sf::IntRect(rect_obj->left, rect_obj->top, rect_obj->width, rect_obj->height));

		rb_iv_set(klass, "@left",   UINT2NUM(rect_obj->left));
		rb_iv_set(klass, "@top",    UINT2NUM(rect_obj->top));
		rb_iv_set(klass, "@width",  UINT2NUM(rect_obj->width));
		rb_iv_set(klass, "@height", UINT2NUM(rect_obj->height)); 

		Bitmap *Bitmap_obj;
		
		VALUE image = rb_iv_get(klass, "@bitmap");
		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		
		if (image != Qnil)
		{
			Data_Get_Struct(image, Bitmap, Bitmap_obj);
			Bitmap_obj->resize(rect_obj->width, rect_obj->height);
		}
		
		return Qnil;
	}

	static VALUE sprite_setPosition(VALUE klass, VALUE x, VALUE y)
	{
		SpriteClass *spriteClass_obj;	
		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		spriteClass_obj->tSprite.setPosition(NUM2DBL(x), NUM2DBL(y));
		rb_iv_set(klass, "@x", x);
		rb_iv_set(klass, "@y", y);
		return Qnil;
	}

	static VALUE sprite_setRotation(VALUE klass, VALUE rotation)
	{
		SpriteClass *spriteClass_obj;
		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		spriteClass_obj->tSprite.setRotation(NUM2DBL(rotation));
		rb_iv_set(klass, "@rotation", rotation);
		return Qnil;
	}

	static VALUE sprite_setOpacity(VALUE klass, VALUE opacity)
	{
		SpriteClass *spriteClass_obj;
		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		sf::Color color = spriteClass_obj->tSprite.getColor();
		spriteClass_obj->tSprite.setColor(sf::Color(color.r, color.g, color.b, NUM2INT(opacity)));
		rb_iv_set(klass, "@opacity", opacity);
		return Qnil;
	}

	static VALUE sprite_changeImage(VALUE klass, VALUE image)
	{
		SpriteClass *spriteClass_obj;
		Bitmap *Bitmap_obj;
		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		Data_Get_Struct(image, Bitmap, Bitmap_obj);

		sf::Texture tex = Bitmap_obj->getTexture();

		cloneBitmap->resize(tex.getSize().x, tex.getSize().y);
		cloneBitmap->clear(Color(0, 0, 0, 0));
		cloneBitmap->drawImage(0, 0, *Bitmap_obj, 0, 0, tex.getSize().x, tex.getSize().y);

		spriteClass_obj->changeImage(*cloneBitmap);

		VALUE newBitmap = Data_Wrap_Struct(rb_path2class("RGA::Bitmap"), 0, bitmap_Free, cloneBitmap);

		rb_iv_set(klass, "@width",  INT2NUM(tex.getSize().x));
		rb_iv_set(klass, "@height", INT2NUM(tex.getSize().y));
		rb_iv_set(klass, "@bitmap", newBitmap);

		return Qnil;
	}

	static VALUE sprite_Update(VALUE klass)
	{
		SpriteClass *spriteClass_obj;
		Bitmap *Bitmap_obj;
		
		VALUE image = rb_iv_get(klass, "@bitmap");
		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		
		if (image != Qnil)
		{
			Data_Get_Struct(image, Bitmap, Bitmap_obj);
			spriteClass_obj->changeImage(*Bitmap_obj);
		}

		return Qtrue;
	}

	static VALUE sprite_setTone(VALUE klass, VALUE color)
	{
		SpriteClass *spriteClass_obj;
		Color *color_obj;

		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		Data_Get_Struct(color, Color, color_obj);

		spriteClass_obj->tSprite.setColor(sf::Color(color_obj->r, color_obj->g, color_obj->b, color_obj->a));
		return Qnil;
	}

	static VALUE sprite_setVisible(VALUE klass, VALUE visible)
	{
		SpriteClass *spriteClass_obj;	
		Data_Get_Struct(klass, SpriteClass, spriteClass_obj);
		spriteClass_obj->setVisible(visible == Qtrue ? true : false);
		rb_iv_set(klass, "@visible", visible);
		return visible;
	} 
}

void spriteInit()
{
	VALUE newSprite = rb_define_class_under(RGA, "Sprite", rb_cObject);
	rb_define_singleton_method(newSprite, "new", (ruby_method*)&sprite_New, 0);
	rb_define_method(newSprite, "dispose",       (ruby_method*)&sprite_Dispose, 0);
	rb_define_method(newSprite, "setRect",       (ruby_method*)&sprite_changeRect, 1);
	rb_define_method(newSprite, "setPosition",   (ruby_method*)&sprite_setPosition, 2);
	rb_define_method(newSprite, "setRotation",   (ruby_method*)&sprite_setRotation, 1);
	rb_define_method(newSprite, "setOpacity",    (ruby_method*)&sprite_setOpacity, 1);
	rb_define_method(newSprite, "update", 		 (ruby_method*)&sprite_Update, 0);
	rb_define_method(newSprite, "setTone",       (ruby_method*)&sprite_setTone, 1);
	rb_define_method(newSprite, "setVisible",    (ruby_method*)&sprite_setVisible, 1);
	rb_define_attr_method(newSprite, "visible",  Qtrue, (ruby_method*)&sprite_setVisible);
	rb_define_attr_method(newSprite, "tone",     Qtrue, (ruby_method*)&sprite_setTone);
	rb_define_attr_method(newSprite, "bitmap",   Qtrue, (ruby_method*)&sprite_changeImage);
	rb_define_attr_method(newSprite, "opacity",  Qtrue, (ruby_method*)&sprite_setOpacity);
	rb_define_attr_method(newSprite, "rotation", Qtrue, (ruby_method*)&sprite_setRotation);
	rb_define_attr_method(newSprite, "x",        Qtrue, (ruby_method*)&sprite_changeX);
	rb_define_attr_method(newSprite, "y",        Qtrue, (ruby_method*)&sprite_changeY);
	rb_define_attr_method(newSprite, "width",    Qtrue, (ruby_method*)&sprite_changeWidth);
	rb_define_attr_method(newSprite, "height",   Qtrue, (ruby_method*)&sprite_changeHeight);
	rb_define_attr_method(newSprite, "left",     Qtrue, (ruby_method*)&sprite_changeLeft);
	rb_define_attr_method(newSprite, "top",      Qtrue, (ruby_method*)&sprite_changeTop);
}
