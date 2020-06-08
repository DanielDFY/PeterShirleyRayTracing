#include <iostream>
#include <fstream>
#include <cstdio>

#include <Color.h>
#include <Ray.h>
#include <HittableList.h>
#include <Sphere.h>
#include <Camera.h>

#include <helperUtils.h>

#define PPM	// produce output.ppm
#define PNG	// produce output.png

#ifdef PNG
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
#endif

Color rayColor(const Ray& r, const Hittable& hittable, const int depthRemaining) {
	if (depthRemaining <= 0) {
		return { 0.0, 0.0, 0.0 };
	}
	
	HitRecord rec;
	if (hittable.hit(r, 0.0001, M_DOUBLE_INFINITY, rec)) {
		const Point3 target = rec.point + rec.normal + randomUnitVec3();
		return 0.5 * rayColor(Ray(rec.point, target - rec.point), hittable, depthRemaining - 1);
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
	constexpr int samplesPerPixel = 100;
	constexpr int maxDepth = 50;

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
	Camera camera;

	// world objects
	HittableList worldObjects;
	worldObjects.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));
	worldObjects.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0));

	/*
	 * the pixels are written out in rows with pixels left to right.
	 * the rows are written out from top to bottom.
	 */
	for (int row = 0; row < imageHeight; ++row) {
		// print progress info during processing
		printf("\rProcessing[%.2lf%%]", static_cast<double>(row * 100.0) / static_cast<double>(imageHeight - 1));

		for (int col = 0; col < imageWidth; ++col) {
			Color pixelColor(0.0, 0.0, 0.0);
			for (size_t s = 0; s < samplesPerPixel; ++s) {
				const auto u = (static_cast<double>(col) + randomDouble()) / static_cast<double>(imageWidth - 1);
				const auto v = 1.0 - (static_cast<double>(row) + randomDouble()) / static_cast<double>(imageHeight - 1);

				const Ray r = camera.getRay(u, v);

				pixelColor += rayColor(r, worldObjects, maxDepth);
			}

			pixelColor /= samplesPerPixel;
			pixelColor.gammaCorrect();
			
			#ifdef PPM
			// write pixel data to output.ppm
			writeColor8bit(outputStream, pixelColor);
			#endif

			#ifdef PNG
			const auto ucr = static_cast<unsigned char>(pixelColor.r8bit());
			const auto ucg = static_cast<unsigned char>(pixelColor.g8bit());
			const auto ucb = static_cast<unsigned char>(pixelColor.b8bit());
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