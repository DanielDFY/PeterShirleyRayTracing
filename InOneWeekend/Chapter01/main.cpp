#include <fstream>

// for .png
// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "../../include/stb/stb_image_write.h"

int main() {
	/* image config */
	constexpr int imageWidth = 256;
	constexpr int imageHeight = 256;

	/* image output file */
	// for .ppm
	std::ofstream outputStream("output.ppm");
	outputStream << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";	// .ppm header
	
	// for .png
	// constexpr int channelNum = 3;
	// constexpr int imageSize = imageHeight * imageWidth * channelNum;
	// constexpr int strideInBytes = imageWidth * channelNum * sizeof(unsigned char);
	// unsigned char pixelData[imageSize];
	// memset(pixelData, 0, imageSize);
	// int currPixelIndex = 0;
	
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

			// for .ppm
			const auto ir = static_cast<int>(255.999 * r);
			const auto ig = static_cast<int>(255.999 * g);
			const auto ib = static_cast<int>(255.999 * b);
			outputStream << ir << ' ' << ig << ' ' << ib << '\n';
			
			// for .png
			// const auto ir = static_cast<unsigned char>(255.999 * r);
			// const auto ig = static_cast<unsigned char>(255.999 * g);
			// const auto ib = static_cast<unsigned char>(255.999 * b);
			// pixelData[currPixelIndex++] = ir;
			// pixelData[currPixelIndex++] = ig;
			// pixelData[currPixelIndex++] = ib;
		}
	}

	// print complete info
	printf("\rProcessing[100.00%%]\nComplete!");

	// for .ppm
	outputStream.close();
	
	// for .png
	// stbi_write_png("output.png", imageWidth, imageHeight, channelNum, pixelData, strideInBytes);
	
	return 0;
}