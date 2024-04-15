//File:CS112_A3_Part1_S11_20231011_20220902_20231006
//Purpose:Fractions Calculator
//Authors: أحمد علاء الدين علي عبد العواض|| أحمد بشير سعد معوض || AhmedEdris
//IDS: 20231011 \ 20220902 \ 20231006


// توزيع المهام :
// 20231011( 3 , 6 , 9 , 12 ) 
// 20231006 ( 2 , 5 , 8 , 11)
// 20220902 (main code , 1 ,4 , 7 , 10 , 16 )


//Emails:
//20231011:ahmedawwad646@gmail.com.
//20231006:besherahmed068@gmail.com
//20220902:ksaai1818@gmail.com.

#include "Image_Class.h"
#include <iostream>
#include <string>


using namespace std;


void printInitialMenu() {
    cout << "\n===== Welcome to the Image Processing Tool =====\n";
    cout << "1. Insert Image\n";
    cout << "2. Exit\n";
    cout << "Enter your choice: ";
   
}


void printImageProcessingMenu() {
    cout << "\nImage Processing Menu:\n";
    cout << "1. Apply Grayscale Filter\n";
    cout << "2. Apply Black and White Filter\n";
    cout << "3. Apply Invert Image Filter\n";
    cout << "4. Merge Images\n";
    cout << "5. Flip Image\n";
    cout << "6. Darken and Lighten Image\n";
    cout << "7. Edge Detection Filter\n";
    cout << "8. purple at night\n";
    cout << "9. Rotate Filter\n";
    cout << "10. Blur filter\n";
    cout << "11. Crop Images\n";
    cout << "12. Resizing Images\n";
    cout << "13. Back to Initial Menu\n";
    cout << "14. Exit\n";
    cout << "Enter your choice: ";
}


void applyGrayscaleFilter(unsigned char* imageData, int width, int height, int channels) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int i = (y * width + x) * channels;
            unsigned char gray = static_cast<unsigned char>(0.299f * imageData[i] + 0.587f * imageData[i + 1] + 0.114f * imageData[i + 2]);
            imageData[i] = gray;
            imageData[i + 1] = gray;
            imageData[i + 2] = gray;
        }
    }
}


void applyBlackAndWhiteFilter(unsigned char* imageData, int width, int height, int channels) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int i = (y * width + x) * channels;
            unsigned char gray = static_cast<unsigned char>(0.299f * imageData[i] + 0.587f * imageData[i + 1] + 0.114f * imageData[i + 2]);
            unsigned char bw = (gray > 128) ? 255 : 0; 
            imageData[i] = bw;
            imageData[i + 1] = bw;
            imageData[i + 2] = bw;
        }
    }
}


void applyInvertImageFilter(unsigned char* imageData, int width, int height, int channels) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int i = (y * width + x) * channels;
            imageData[i] = 255 - imageData[i];
            imageData[i + 1] = 255 - imageData[i + 1];
            imageData[i + 2] = 255 - imageData[i + 2];
        }
    }
}


void mergeImages(unsigned char* imageData1, const unsigned char* imageData2, int width, int height, int channels) {
    
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            
            int index = (y * width + x) * channels;

            
            unsigned char r = (imageData1[index] + imageData2[index]) / 2;
            unsigned char g = (imageData1[index + 1] + imageData2[index + 1]) / 2;
            unsigned char b = (imageData1[index + 2] + imageData2[index + 2]) / 2;

            
            imageData1[index] = r;
            imageData1[index + 1] = g;
            imageData1[index + 2] = b;
        }
    }
}



void flipImageHorizontal(unsigned char* imageData, int width, int height, int channels) {
    int halfWidth = width / 2;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < halfWidth; ++x) {
            int i = (y * width + x) * channels;
            int j = ((y + 1) * width - x - 1) * channels;
            for (int c = 0; c < channels; ++c) {
                std::swap(imageData[i + c], imageData[j + c]);
            }
        }
    }
    cout << "Image flipped horizontally.\n";
}


void flipImageVertical(unsigned char* imageData, int width, int height, int channels) {
    int halfHeight = height / 2;
    for (int y = 0; y < halfHeight; ++y) {
        for (int x = 0; x < width; ++x) {
            int i = (y * width + x) * channels;
            int j = ((height - y - 1) * width + x) * channels;
            for (int c = 0; c < channels; ++c) {
                std::swap(imageData[i + c], imageData[j + c]);
            }
        }
    }
    cout << "Image flipped vertically.\n";
}
void applyDarkenFilter(unsigned char* imageData, int width, int height, int channels) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int i = (y * width + x) * channels;
            for (int c = 0; c < channels; ++c) {
                imageData[i + c] = static_cast<unsigned char>(std::max(0, imageData[i + c] - (imageData[i + c] * 50) / 100));
            }
        }
    }
}

void applyLightenFilter(unsigned char* imageData, int width, int height, int channels) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int i = (y * width + x) * channels;
            for (int c = 0; c < channels; ++c) {
                imageData[i + c] = std::min(255, imageData[i + c] + (imageData[i + c] * 50) / 100);
            }
        }
    }
}
void applyDarkenOrLightenFilter(unsigned char* imageData, int width, int height, int channels) {
    int choice;
    cout << "Do you want to darken or lighten the image? (1 for darken, 2 for lighten): ";
    cin >> choice;

    if (choice == 1) {
        applyDarkenFilter(imageData, width, height, channels);
        cout << "Image darkened by 50%.\n";
    } else if (choice == 2) {
        applyLightenFilter(imageData, width, height, channels);
        cout << "Image lightened by 50%.\n";
    } else {
        cerr << "Error: Invalid choice. Please enter 1 for darken or 2 for lighten.\n";
        return;
    }
}

void applyEdgeDetectionFilter(unsigned char* imageData, int width, int height, int channels) {
    
    unsigned char* tempData = new unsigned char[width * height * channels];
    memset(tempData, 255, width * height * channels); 

    
    int sobelX[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int sobelY[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

    
    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            for (int c = 0; c < channels; ++c) {
                int gx = 0, gy = 0;
                for (int ky = -1; ky <= 1; ++ky) {
                    for (int kx = -1; kx <= 1; ++kx) {
                        int index = ((y + ky) * width + (x + kx)) * channels + c;
                        gx += imageData[index] * sobelX[ky + 1][kx + 1];
                        gy += imageData[index] * sobelY[ky + 1][kx + 1];
                    }
                }
                int index = (y * width + x) * channels + c;
                
                unsigned char gradientMagnitude = static_cast<unsigned char>(sqrt(gx * gx + gy * gy));
                
                tempData[index] = (gradientMagnitude > 128) ? 0 : 255;
            }
        }
    }

    
    memcpy(imageData, tempData, width * height * channels);

    
    delete[] tempData;
}



void applyPurpleNightFilter(Image& img) {
    const float redFactor = 1.5f;   
    const float greenFactor = 0.5f; 
    const float blueFactor = 0.8f;  

    
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            
            unsigned char& r = img(x, y, 0); 
            unsigned char& g = img(x, y, 1); 
            unsigned char& b = img(x, y, 2); 

            
            r = static_cast<unsigned char>(std::min(255.0f, redFactor * r));   
            g = static_cast<unsigned char>(std::max(0.0f, greenFactor * g));   
            b = static_cast<unsigned char>(std::max(0.0f, blueFactor * b));    
        }
    }
}


void RotateFilter(unsigned char* imageData, int width, int height, int channels) {
    // Check if the image dimensions are compatible with a 90-degree rotation
    if (width <= 0 || height <= 0 || channels <= 0) {
        std::cerr << "Error: Invalid image dimensions or channels.\n";
        return;
    }

    // Create a temporary buffer to store the rotated image data
    unsigned char* rotatedImageData = new unsigned char[width * height * channels];

    // Perform a 90-degree clockwise rotation
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int sourceIndex = (y * width + x) * channels;
            int targetIndex = ((width - 1 - x) * height + y) * channels; // Rotate clockwise
            for (int c = 0; c < channels; ++c) {
                rotatedImageData[targetIndex + c] = imageData[sourceIndex + c];
            }
        }
    }

    // Copy the rotated image data back to the original image buffer
    std::copy(rotatedImageData, rotatedImageData + width * height * channels, imageData);

    // Free the temporary buffer
    delete[] rotatedImageData;

    std::cout << "Image rotated 90 degrees clockwise.\n";
}

// BlurFilter function to apply a simple blur effect to the image
void BlurFilter(unsigned char* imageData, int width, int height, int channels) {
    // Create a temporary buffer to hold blurred image data
    unsigned char* blurredImageData = new unsigned char[width * height * channels];

    // Define the blur kernel
    float kernel[3][3] = {
        {1.0f / 9, 1.0f / 9, 1.0f / 9},
        {1.0f / 9, 1.0f / 9, 1.0f / 9},
        {1.0f / 9, 1.0f / 9, 1.0f / 9}
    };

    // Apply blur operation
    for (int x = 1; x < width - 1; ++x) {
        for (int y = 1; y < height - 1; ++y) {
            for (int k = 0; k < channels; ++k) { // for each color channel (R, G, B)
                float sum = 0.0f;
                for (int i = -1; i <= 1; ++i) {
                    for (int j = -1; j <= 1; ++j) {
                        int index = ((y + j) * width + (x + i)) * channels + k;
                        sum += imageData[index] * kernel[i + 1][j + 1];
                    }
                }
                blurredImageData[(y * width + x) * channels + k] = static_cast<unsigned char>(sum);
            }
        }
    }

    // Copy blurred image data back to the original buffer
    memcpy(imageData, blurredImageData, width * height * channels);

    // Free the temporary buffer
    delete[] blurredImageData;

    cout << "Image blurred successfully.\n";
}


// Function to crop the image
void cropImage(Image& img, int x, int y, int width, int height) {
    // Check if the specified crop area is within the bounds of the original image
    if (x < 0 || y < 0 || width <= 0 || height <= 0 || x + width > img.width || y + height > img.height) {
        cerr << "Error: Invalid crop dimensions. Please ensure the crop area is within the image boundaries.\n";
        return;
    }

    // Calculate the number of channels in the image
    int channels = img.channels;

    // Calculate the size of the cropped image
    int croppedWidth = width;
    int croppedHeight = height;

    // Create a new Image object to store the cropped image
    Image croppedImage(croppedWidth, croppedHeight);

    // Copy the pixels from the original image to the cropped image
    for (int j = 0; j < croppedHeight; ++j) {
        for (int i = 0; i < croppedWidth; ++i) {
            for (int c = 0; c < channels; ++c) {
                // Get pixel value from original image
                unsigned char pixelValue = img.getPixel(x + i, y + j, c);
                // Set pixel value in cropped image
                croppedImage.setPixel(i, j, c, pixelValue);
            }
        }
    }

    // Replace the original image with the cropped image
    img = croppedImage;

  cout << "Image cropped successfully.\n";
}


// Function to resize the image based on new dimensions or scaling ratio
void ResizeImage(unsigned char*& imageData, int& width, int& height, int channels) {
    int newWidth, newHeight;
    float ratio;

    cout << "Enter the new width of the image: ";
    cin >> newWidth;
   cout << "Enter the new height of the image: ";
    cin >> newHeight;

    // Calculate scaling ratios for width and height
    float widthRatio = static_cast<float>(newWidth) / width;
    float heightRatio = static_cast<float>(newHeight) / height;

    // Create a temporary buffer for resized image data
    unsigned char* resizedImageData = new unsigned char[newWidth * newHeight * channels];

    // Perform resizing operation
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            int sourceX = static_cast<int>(x / widthRatio);
            int sourceY = static_cast<int>(y / heightRatio);
            int sourceIndex = (sourceY * width + sourceX) * channels;
            int targetIndex = (y * newWidth + x) * channels;
            for (int c = 0; c < channels; ++c) {
                resizedImageData[targetIndex + c] = imageData[sourceIndex + c];
            }
        }
    }

    // Update the image dimensions and replace the image data
    width = newWidth;
    height = newHeight;
    delete[] imageData;
    imageData = resizedImageData;

    cout << "Image resized successfully.\n";
}


bool saveImage(const string& filename, unsigned char* imageData, int width, int height, int channels, const string& format) {
    int result = 0;
    if (format == "JPEG" || format == "jpg") {
        result = stbi_write_jpg(filename.c_str(), width, height, channels, imageData, 100);
    } else if (format == "PNG" || format == "png") {
        result = stbi_write_png(filename.c_str(), width, height, channels, imageData, width * channels);
    } else if (format == "BMP" || format == "bmp") {
        result = stbi_write_bmp(filename.c_str(), width, height, channels, imageData);
    } else {
        cerr << "Error: Unsupported image format.\n";
        return false;
    }

    if (result != 0) {
        cout << "Image saved as " << format << " format.\n";
        return true;
    } else {
        cerr << "Error: Failed to save image.\n";
        return false;
    }
}


int main() {
    Image img;
    string filename;
    int choice;

    while (true) {
        printInitialMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the filename to load: ";
                cin >> filename;
                if (img.loadNewImage(filename)) {
                    cout << "Image loaded successfully.\n";
                    while (true) {
                        printImageProcessingMenu();
                        cin >> choice;

                        switch (choice) {
            case 1:
                if (img.imageData != nullptr) {
                    applyGrayscaleFilter(img.imageData, img.width, img.height, img.channels);
                    cout << "Grayscale filter applied.\n";
                } else {
                    cerr << "Error: No image loaded.\n";
                }
                break;
            case 2:
                if (img.imageData != nullptr) {
                    applyBlackAndWhiteFilter(img.imageData, img.width, img.height, img.channels);
                    cout << "Black and white filter applied.\n";
                } else {
                    cerr << "Error: No image loaded.\n";
                }
                break;
            case 3:
                if (img.imageData != nullptr) {
                    applyInvertImageFilter(img.imageData, img.width, img.height, img.channels);
                    cout << "Invert image filter applied.\n";
                } else {
                    cerr << "Error: No image loaded.\n";
                }
                break;
            case 4:
                if (img.imageData != nullptr) {
                    string filename2;
                    cout << "Enter the filename of the second image to merge: ";
                    cin >> filename2;
                    Image img2;
                    if (img2.loadNewImage(filename2)) {
                        if (img.width == img2.width && img.height == img2.height && img.channels == img2.channels) {
                            mergeImages(img.imageData, img2.imageData, img.width, img.height, img.channels);
                                                        cout << "Images merged successfully.\n";
                        } else {
                            cerr << "Error: Images have different dimensions. Cannot merge.\n";
                        }
                    } else {
                        cerr << "Error: Failed to load second image.\n";
                    }
                } else {
                    cerr << "Error: No image loaded.\n";
                }
                break;
            case 5:
                if (img.imageData != nullptr) {
                    string flipDirection;
                    cout << "Enter the direction to flip (h for horizontal, v for vertical): ";
                    cin >> flipDirection;
                    if (flipDirection == "h" || flipDirection == "H") {
                        flipImageHorizontal(img.imageData, img.width, img.height, img.channels);
                    } else if (flipDirection == "v" || flipDirection == "V") {
                        flipImageVertical(img.imageData, img.width, img.height, img.channels);
                    } else {
                        cerr << "Error: Invalid flip direction. Use 'h' for horizontal or 'v' for vertical.\n";
                    }
                } else {
                    cerr << "Error: No image loaded.\n";
                }
                break;
            case 6:
            if (img.imageData != nullptr) {
                applyDarkenOrLightenFilter(img.imageData, img.width, img.height, img.channels);
            } else {
                cerr << "Error: No image loaded.\n";
            }
                break; 
           
            case 7:
            if (img.imageData != nullptr) {
              applyEdgeDetectionFilter(img.imageData, img.width, img.height, img.channels);
                                cout << "Edge detection filter applied.\n";

            }
            break;
            case 8: 
                if (img.imageData != nullptr) {
                    applyPurpleNightFilter(img);
                    cout << "Purple night filter applied.\n";
                } else {
                    cerr << "Error: No image loaded. Please load an image first.\n";
                }
                break;
              case 9:
                 if (img.imageData != nullptr) {
                    // Rotate image 90 degrees clockwise
                    RotateFilter(img.imageData, img.width, img.height, img.channels);
                } else {
                    cerr << "Error: No image loaded. Please load an image first.\n";
                }
                break;

            case 10:
                 if (img.imageData != nullptr) {
                    // Apply blur filter to the image
                    BlurFilter(img.imageData, img.width, img.height, img.channels);
                } else {
                    std::cerr << "Error: No image loaded. Please load an image first.\n";
                }
                break;

            case 11: 
            if (img.imageData != nullptr) {
                    int x, y, width, height;
                    cout << "Enter x-coordinate of top-left corner: ";
                    cin >> x;
                    cout << "Enter y-coordinate of top-left corner: ";
                    cin >> y;
                    cout << "Enter width of the cropped area: ";
                    cin >> width;
                    cout << "Enter height of the cropped area: ";
                    cin >> height;
                    cropImage(img, x, y, width, height);
                } else {
                   cerr << "Error: No image loaded. Please load an image first.\n";
                }
                break;
            
            case 12: 
             if (img.imageData != nullptr) {
                    
                    ResizeImage(img.imageData, img.width, img.height, img.channels);
                    
                } else {
                    std::cerr << "Error: No image loaded. Please load an image first.\n";
                }
                break;
            case 13: {

break;


            }
            case 14:
        
                                
                                cout << "Exiting...\n";
                                return 0;
                            default:
                                cerr << "Error: Invalid choice. Please try again.\n";
                                break;
                        }


if (choice >= 1 && choice <= 12 && img.imageData != nullptr) {
                            string format;
                            string imagename;
                            cout << "Enter image name: ";
                            cin >> imagename;
                            imagename = imagename + ".";
                            cout << "Enter the format to save the image (JPEG, JPG, PNG, BMP): ";
                            cin >> format;
                            if (saveImage(imagename + format, img.imageData, img.width, img.height, img.channels, format)) {
                               
                            } else {
                                cerr << "Error: Failed to save image.\n";
                            }
                        } else if (choice == 13
                        ) {
                            break;
                            
                        } else {
                            cerr << "Error: No image loaded or invalid choice for saving.\n";
                        }
                    }
                } else {
                    cerr << "Error: Failed to load image.\n";
                }
                break;
            case 2:
                
                cout << "Exiting...\n";
                return 0;
            default:
                cerr << "Error: Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0; 
}











