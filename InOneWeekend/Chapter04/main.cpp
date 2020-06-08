#include <iostream>
#include <fstream>
#include <cstdio>

#include <Color.h>
#include <Ray.h>

#define PPM	// produce output.ppm
#define PNG	// produce output.png

#ifdef PNG
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
#endif

bool hitSphere(const Point3& center,const double radius, const Ray& r) {
	const Vec3 oc = r.origin() - center;
	const double a = dot(r.direction(), r.direction());
	const double b = 2.0 * dot(oc, r.direction());
	const double c = dot(oc, oc) - radius * radius;
	const double discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

Color rayColor(const Ray& r) {
	if (hitSphere(Point3(0.0, 0.0, -1.0), 0.5, r)) {
		return {1.0, 0.0, 0.0};
	}
	
	const Vec3 unitDirection = unitVec3(r.direction());
	const double t = 0.5 * (unitDirection.y() + 1.0);
	return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

int main() {
	/* image config */
	constexpr double aspectRatio = 16.0 / 9.0;
	constexpr int imageWidth = 384;
	constexpr auto imageHeight = static_cast<int>(imageWidth / aspectRatio);

	/* image output file */
	const std::string fileName("output");

	#ifdef PPM
	// preparation
	const std::string ppmFileName(fileName + ".ppm");
	std::ofstream outputStream(ppmFileName);
	if (!outputStream.is_open()) {
		std::cerr << "failed to open file " << ppmFileName << std::endl;
		exit(EXIT_FAILURE);
	}

	// .ppm header
	outputStream << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
	#endif

	#ifdef PNG
	// preparation
	const std::string pngFileName(fileName + ".png");
	constexpr int channelNum = 3;
	constexpr int imageSize = imageWidth * imageHeight * channelNum;
	constexpr size_t strideInBytes = imageWidth * channelNum * sizeof(unsigned char);

	const std::unique_ptr<unsigned char[]> pixelDataPtr(new unsigned char[imageSize]);
	int idx = 0;
	#endif

	/* camera config */
	constexpr double viewPortHeight = 2.0;
	constexpr double viewPortWidth = aspectRatio * viewPortHeight;
	constexpr double focalLength = 1.0;

	const Point3 origin(0.0, 0.0, 0.0);
	const Vec3 horizontal(viewPortWidth, 0.0, 0.0);
	const Vec3 vertical(0.0, viewPortHeight, 0.0);
	const Point3 lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - Vec3(0.0, 0.0, focalLength);
	
	/*
	 * the pixels are written out in rows with pixels left to right.
	 * the rows are written out from top to bottom.
	 */
	for (int row = 0; row < imageHeight; ++row) {
		// print progress info during processing
		printf("\rProcessing[%.2lf%%]", static_cast<double>(row * 100.0) / static_cast<double>(imageHeight - 1));

		for (int col = 0; col < imageWidth; ++col) {
			const auto u = static_cast<double>(col) / static_cast<double>(imageWidth - 1);
			const auto v = 1.0 - static_cast<double>(row) / static_cast<double>(imageHeight - 1);
			
			const Ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);

			const Color color = rayColor(r);
			
			#ifdef PPM
			// write pixel data to output.ppm
			writeColor8bit(outputStream, color);
			#endif

			#ifdef PNG
			const auto ucr = static_cast<unsigned char>(color.r8bit());
			const auto ucg = static_cast<unsigned char>(color.g8bit());
			const auto ucb = static_cast<unsigned char>(color.b8bit());
			// store pixel data
			pixelDataPtr[idx++] = ucr;
			pixelDataPtr[idx++] = ucg;
			pixelDataPtr[idx++] = ucb;
			#endif
		}
	}

	// print complete info
	printf("\rProcessing[100.00%%]\nComplete!\n");

	#ifdef PPM
	// close output.ppm
	outputStream.close();
	#endif

	#ifdef PNG
	// write pixel data to output.png
	stbi_write_png(pngFileName.c_str(), imageWidth, imageHeight, channelNum, pixelDataPtr.get(), strideInBytes);
	#endif

	return 0;
}