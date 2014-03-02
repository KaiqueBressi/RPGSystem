#include "Image.hpp"

Bitmap::Bitmap(unsigned int width, unsigned int height)
{
	tRenderTexture = new sf::RenderTexture();
	tRenderTexture->create(width, height);
	tRenderTexture->clear(sf::Color(255, 255, 255));
	tRenderTexture->display();
}

Bitmap::Bitmap(std::string filename)
{
	tRenderTexture = new sf::RenderTexture();
	
	sf::Texture tex = sf::Texture();
	tex.loadFromFile(filename);
	sf::Sprite sprite(tex);

	tRenderTexture->create(sprite.getTextureRect().width, sprite.getTextureRect().height);
	tRenderTexture->clear(sf::Color(0, 0, 0, 0));
	tRenderTexture->draw(sprite);
	tRenderTexture->display();
}

void Bitmap::drawText(std::string text, float x, float y)
{
	sf::Font tFont;
	tFont.loadFromFile("segoe_ui.ttf");

	sf::Text tText(text, tFont);
	tText.setCharacterSize(72);
	tText.setColor(sf::Color(255, 0, 0));
	tText.setPosition(sf::Vector2f(x, y));

	tRenderTexture->draw(tText);
	tRenderTexture->display();
}

void Bitmap::drawImage(float x, float y, Bitmap image, unsigned int left, unsigned int top, unsigned int width, unsigned int height)
{
	sf::Texture tex = image.getTexture();
	sf::Sprite sprite(tex);
	sprite.setPosition(sf::Vector2f(x, y));
	sprite.setTextureRect(sf::IntRect(left, top, width, height));
	tRenderTexture->draw(sprite);
	tRenderTexture->display();
}

void Bitmap::clear(Color color)
{
	tRenderTexture->clear(sf::Color(color.r, color.g, color.b, color.a));
	tRenderTexture->display();
}

void Bitmap::resize(unsigned int width, unsigned height)
{
	sf::Texture tex = tRenderTexture->getTexture();
	sf::Sprite sprite(tex);
	tRenderTexture->clear(sf::Color(0, 0, 0, 0));
	tRenderTexture->create(width, height);
	tRenderTexture->draw(sprite);
	tRenderTexture->display();
}

sf::Texture Bitmap::getTexture()
{
	sf::Texture tex = tRenderTexture->getTexture();
	return tex;
}

extern "C"
{
	static VALUE bitmap_Free(Bitmap *imageObj)
	{
		delete imageObj;
		return Qnil;
	}

	static VALUE bitmap_New(int argc, VALUE *argv, VALUE klass)
	{
	 	Bitmap *imageObj;

	 	if (argc == 1)
	 		imageObj = new Bitmap(StringValuePtr(argv[0]));
	 	else
	 		imageObj = new Bitmap(NUM2UINT(argv[0]), NUM2UINT(argv[1]));

		VALUE newBitmap = Data_Wrap_Struct(klass, 0, bitmap_Free, imageObj);
		return newBitmap;
	}

	static VALUE bitmap_drawText(VALUE klass, VALUE text, VALUE x, VALUE y)
	{
		Bitmap *Bitmap_obj;	
		Data_Get_Struct(klass, Bitmap, Bitmap_obj);
		Bitmap_obj->drawText(StringValuePtr(text), NUM2DBL(x), NUM2DBL(y));
		return Qnil;
	}

	static VALUE bitmap_drawImage(VALUE klass, VALUE x, VALUE y, VALUE image, VALUE rect)
	{
		Bitmap *Bitmap_obj;	
		Bitmap *imageObj;
		Rect *rect_obj;

		Data_Get_Struct(klass, Bitmap, Bitmap_obj);
		Data_Get_Struct(image, Bitmap, imageObj);
		Data_Get_Struct(rect, Rect, rect_obj);

		Bitmap_obj->drawImage(NUM2DBL(x), NUM2DBL(y), *imageObj, rect_obj->left, rect_obj->top, rect_obj->width, rect_obj->height);
		return Qnil;
	}

	static VALUE bitmap_Clear(VALUE klass, VALUE color)
	{
		Bitmap *Bitmap_obj;
		Color *color_obj;

		Data_Get_Struct(klass, Bitmap, Bitmap_obj);
		Data_Get_Struct(color, Color, color_obj);

		Bitmap_obj->clear(*color_obj);
		return Qnil;
	}
}

void bitmapInit()
{
	VALUE newBitmap = rb_define_class_under(RGA, "Bitmap", rb_cObject);
	rb_define_singleton_method(newBitmap, "new", (ruby_method*)&bitmap_New, -1);
	rb_define_method(newBitmap, "drawText",   (ruby_method*)&bitmap_drawText, 3);
	rb_define_method(newBitmap, "drawBitmap", (ruby_method*)&bitmap_drawImage, 4);
	rb_define_method(newBitmap, "clear",      (ruby_method*)&bitmap_Clear, 1);
} 