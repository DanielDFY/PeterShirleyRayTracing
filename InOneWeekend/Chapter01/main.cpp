#include <iostream>
#include <fstream>
#include <cstdio>

#define PPM	// produce output.ppm
#define PNG	// produce output.png

#ifdef PNG
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
#endif

int main() {
	/* image config */
	constexpr int imageWidth = 256;
	constexpr int imageHeight = 256;

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

	/*
	 * the pixels are written out in rows with pixels left to right.
	 * the rows are written out from top to bottom.
	 */
	for (int row = 0; row < imageHeight; ++row) {
		// print progress info during processing
		printf("\rProcessing[%.2lf%%]", static_cast<double>(row * 100.0) / static_cast<double>(imageHeight - 1));

		for (int col = 0; col < imageWidth; ++col) {
			const double r = static_cast<double>(row) / static_cast<double>(imageHeight - 1);
			const double g = static_cast<double>(col) / static_cast<double>(imageWidth - 1);
			const double b = 0.25;

			#ifdef PPM
			const auto ir = static_cast<int>(255 * r);
			const auto ig = static_cast<int>(255 * g);
			const auto ib = static_cast<int>(255 * b);
			// write pixel data to output.ppm
			outputStream << ir << ' ' << ig << ' ' << ib << '\n';
			#endif

			#ifdef PNG
			const auto ucr = static_cast<unsigned char>(255 * r);
			const auto ucg = static_cast<unsigned char>(255 * g);
			const auto ucb = static_cast<unsigned char>(255 * b);
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