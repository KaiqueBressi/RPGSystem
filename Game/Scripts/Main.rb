@a = RGA::Bitmap.new("Fighter.png")

@b = RGA::Sprite.new
@b.bitmap = @a
@b.tone = RGA::Color.new(255, 0, 0)
@b.visible = false
@b.update

loop do
	RGA::Graphics.update
end
