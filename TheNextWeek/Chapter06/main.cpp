#include <iostream>
#include <fstream>
#include <cstdio>

#include <Color.h>
#include <Ray.h>
#include <HittableList.h>
#include <Sphere.h>
#include <Camera.h>
#include <Material.h>
#include <BVH.h>
#include <AARect.h>

#include <helperUtils.h>

#define PPM	// produce output.ppm
#define PNG	// produce output.png

#ifdef PNG
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
#endif

HittableList cornellBox() {
	HittableList objects;

	auto redMat = std::make_shared<Lambertian>(Color(0.65, 0.05, 0.05));
	auto whiteMat = std::make_shared<Lambertian>(Color(0.73, 0.73, 0.73));
	auto greenMat = std::make_shared<Lambertian>(Color(0.12, 0.45, 0.15));
	auto lightMat = std::make_shared<DiffuseLight>(Color(15.0, 15.0, 15.0));

	objects.add(std::make_shared<YZRect>(0.0, 555.0, 0.0, 555.0, 555.0, greenMat));
	objects.add(std::make_shared<YZRect>(0.0, 555.0, 0.0, 555.0, 0.0, redMat));
	objects.add(std::make_shared<XZRect>(213.0, 343.0, 227.0, 332.0, 554.0, lightMat));
	objects.add(std::make_shared<XZRect>(0.0, 555.0, 0.0, 555.0, 0.0, whiteMat));
	objects.add(std::make_shared<XZRect>(0.0, 555.0, 0.0, 555.0, 555.0, whiteMat));
	objects.add(std::make_shared<XYRect>(0.0, 555.0, 0.0, 555.0, 555.0, whiteMat));
	
	return objects;
}

Color rayColor(const Ray& r, const Color& background, const Hittable& hittable, const int depthRemaining) {
	if (depthRemaining <= 0) {
		return { 0.0, 0.0, 0.0 };
	}
	
	HitRecord rec;
	if (!hittable.hit(r, 0.0001, M_DOUBLE_INFINITY, rec))
		return background;

	Ray scattered;
	Color attenuation;
	Color emitted = rec.matPtr->emitted(rec.u, rec.v, rec.point);
	
	if (!rec.matPtr->scatter(r, rec, attenuation, scattered)) {
		return emitted;
	}
	return emitted + attenuation * rayColor(scattered, background, hittable, depthRemaining - 1);
}

int main() {
	/* image config */
	constexpr double aspectRatio = 1.0;
	constexpr int imageWidth = 600;
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
	const Point3 lookFrom(278.0, 278.0, -800.0);
	const Point3 lookAt(278.0, 278.0, 0.0);
	const Vec3 vUp(0, 1, 0);
	const double vFov = 40.0;
	const double aperture = 0.0;
	const double distToFocus = 10.0;
	const double time0 = 0.0;
	const double time1 = 0.0;
	const Color background(0.0, 0.0, 0.0);
	
	Camera camera(lookFrom, lookAt, vUp, vFov, aspectRatio, aperture, distToFocus, time0, time1);

	// world objects
	HittableList worldObjects = cornellBox();
	BVHNode worldObjectsBVHTree(worldObjects, time0, time1);

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

				pixelColor += rayColor(r, background, worldObjectsBVHTree, maxDepth);
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