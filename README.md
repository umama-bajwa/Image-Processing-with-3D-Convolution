# 3D Convolution for Image Processing
This project involves implementing 3D convolution operations using C++ and OpenCV. It encompasses various functions such as blurring, edge detection, and feature extraction specifically designed for 3D grayscale images. The implementation ensures precise handling of image borders through the use of zero-padding, maintaining image integrity and accuracy in processing.


## Installation

To install the OpenCV library, Visit: https://opencv.org/releases/

Choose the appropriate version for your system. Follow the instructions provided on the website to complete the installation process.

```bash
  cd https://github.com/umama-bajwa/Image-Processing-with-3D-Convolution
```


Download and execute the files:

- https://github.com/umama-bajwa/Image-Processing-with-3D-Convolution/blob/main/3D_convolution.h

- https://github.com/umama-bajwa/Image-Processing-with-3D-Convolution/blob/main/3D_convolution.cpp
## Usage/Examples
#### 1. Loading  a 3D Image:

Ensure that your 3D grayscale image is in the correct format (TIFF file) and is placed in the project directory.

Utilize the provided function in your code to load the image

```javascript
//obj
    Mat img;

    //----------------------------------------Loading the grayscale image

    img = imread("path/to/your/image.file", IMREAD_GRAYSCALE);
```

#### 2. Applying the 3D Convolution:


- for blurring:

```javascript
apply3DConvolution(arr, img_rows, img_cols);
```

- for edge detection:

```javascript
 apply3DConvolutionEdgeDetection(arr, img_rows, img_cols, edgeDetected);
```

- for feature extraction:

```javascript
 apply3DConvolutionFeatureExtraction(arr, img_rows, img_cols)
```

## Features

- Loading 3D Images
- Performing Blurring Convolution
- Conducting Edge Detection Convolution
- Executing Feature Extraction Convolution
- Handling Image Borders
- Saving Processed Images


## Screenshots
- Blurred Image:
  
![Blurred Image](https://github.com/umama-bajwa/Image-Processing-with-3D-Convolution/assets/173785404/c272a715-037e-4f9a-a2c6-db6f8b98dbf9)

- Edge Detected Image:
  
![EdgeDetectedImage](https://github.com/umama-bajwa/Image-Processing-with-3D-Convolution/assets/173785404/800e84fc-ad47-4595-bcc9-a133c044501f)

- Feature Extracted Image:
  
![FeatureExtractedImage](https://github.com/umama-bajwa/Image-Processing-with-3D-Convolution/assets/173785404/e07175d7-9897-441f-a9bd-c9407d00674a)



## Contributing

Contributions are always welcome!

See `contributing.md` for ways to get started.




## Documentation

[Documentation](https://docs.opencv.org/4.x/index.html)



