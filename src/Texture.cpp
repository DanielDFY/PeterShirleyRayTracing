#include <Texture.h>

// Disable pedantic warnings for this external library.
#ifdef _MSC_VER
	// Microsoft Visual C++ Compiler
	#pragma warning (push, 0)
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

// Restore warning levels.
#ifdef _MSC_VER
	// Microsoft Visual C++ Compiler
	#pragma warning (pop)
#endif

Color CheckerTexture::value(double u, double v, const Point3& point) const {
	const double sines = sin(10 * point.x()) * sin(10 * point.y()) * sin(10 * point.z());
	return sines < 0 ? _oddTexture->value(u, v, point) : _evenTexture->value(u, v, point);
}

ImageTexture::ImageTexture(const char* fileName) {
	auto componentsPerPixel = bytesPerPixel;
	_data = stbi_load(fileName, &_width, &_height, &componentsPerPixel, componentsPerPixel);
	if (_data == nullptr) {
		std::cerr << "ERROR: Could not load texture image file '" << fileName << "'.\n";
		_width = _height = 0;
	}

	_bytesPerScanline = bytesPerPixel * _width;
}

Color ImageTexture::value(double u, double v, const Point3& point) const {
	// If we have no texture data, then return solid cyan as a debugging aid.
	if (_data == nullptr)
		return { 0.0, 1.0, 1.0 };

	// Clamp input texture coordinates to [0, 1] x [1, 0]
	u = clamp(u, 0.0, 1.0);
	v = 1.0 - clamp(v, 0.0, 1.0);  // Flip V to image coordinates

	auto i = static_cast<int>(u * _width);
	auto j = static_cast<int>(v * _height);

	// Clamp integer mapping, since actual coordinates should be less than 1.0
	if (i >= _width)  i = _width - 1;
	if (j >= _height) j = _height - 1;

	const auto colorScale = 1.0 / 255.0;
	auto pixel = _data + j * _bytesPerScanline + i * bytesPerPixel;

	return { colorScale * pixel[0], colorScale * pixel[1], colorScale * pixel[2] };
}
