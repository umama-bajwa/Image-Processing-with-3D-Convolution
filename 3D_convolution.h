
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//-------------------------------------------- Function to read a grayscale img & stoing in 3d array
void store3DImage(const Mat& img, int*** arr)
{
    int img_rows = img.rows, img_cols = img.cols;
    int img_depth = 1; // Depth is the third dimension, 1 for grayscale bcz no other color (RGB)

    // Iterate over each pixel in the image
    //img rows
    for (int i = 0; i < img_rows; i++)
    {
        //img cols
        for (int j = 0; j < img_cols; j++)
        {
            // Access the intensity value using img.at<uchar>(i, j) & store it in the appropriate position in the 3D array
            for (int k = 0; k < img_depth; k++)
            {
                arr[i][j][k] = img.at<uchar>(i, j * img_depth + k);  //unsigned char
            }
        }
    }
}



//-------------------------------------------- Function to print the 3D image
void print3DImage(int*** arr, int rows, int cols)
{
    //iterates over the image rows
    for (int i = 0; i < rows; ++i)
    {
        //iterates over the image cols
        for (int j = 0; j < cols; ++j)
        {
            //third dim ,, limited to one because grayscale img has only one channel
            for (int k = 0; k < 1; ++k)
            {
                cout << arr[i][j][k] << " ";      //arr[i][j][k] represents the intensity value of the pixel at position (i, j)
            }
            cout << endl;
        }
        cout << endl;
    }
}



//-------------------------------------------- Function to blur the img
void apply3DConvolution(int*** arr, int rows, int cols)
{
    // Defining a 3d blurring kernel
    float kernel[3][3][3] = {
    {{1.f / 64, 2.f / 64, 1.f / 64}, {2.f / 64, 4.f / 64, 2.f / 64}, {1.f / 64, 2.f / 64, 1.f / 64}},
    {{2.f / 64, 4.f / 64, 2.f / 64}, {4.f / 64, 8.f / 64, 4.f / 64}, {2.f / 64, 4.f / 64, 2.f / 64}},
    {{1.f / 64, 2.f / 64, 1.f / 64}, {2.f / 64, 4.f / 64, 2.f / 64}, {1.f / 64, 2.f / 64, 1.f / 64}}
    };

    //temporary array to store the blurred image
    int*** tempArr_blur = new int** [rows];
    for (int i = 0; i < rows; i++)
    {
        //allocations
        tempArr_blur[i] = new int* [cols];

        for (int j = 0; j < cols; j++)
        {
            // Allocating memory for each channel in the pixel
           // Only considering one channel --- grayscale img
            tempArr_blur[i][j] = new int[1];
        }
    }

    // Applying the 3D convolution
    // Iterate over each pixel in the image
    //excluding the border pixels

    //rows
    for (int i = 1; i < rows - 1; ++i)
    {
        //cols
        for (int j = 1; j < cols - 1; ++j)
        {
            //kernel rows
            float blur_sum = 0.0;

            for (int k = -1; k <= 1; ++k)
            {
                //kernel cols
                for (int m = -1; m <= 1; ++m)
                {
                    //kernel depthh
                    for (int n = -1; n <= 1; ++n)
                    {
                        //multiply the image pixel value with the kernel value
                        blur_sum += arr[i + k][j + m][0] * kernel[k + 1][m + 1][n + 1]; // Convolution
                    }
                }
            }

            // Store the result in the blurred array, saturating the result to fit into 8-bit unsigned char range
            tempArr_blur[i][j][0] = saturate_cast<uchar>(blur_sum);
        }
    }

    // Copy the blurred array back to the original array
    for (int i = 1; i < rows - 1; ++i)
    {
        for (int j = 1; j < cols - 1; ++j)
        {

            // Assign the blurred pixel value from the temporary array to the 
            //corresponding position in the original array
            arr[i][j][0] = tempArr_blur[i][j][0];
        }
    }

    // Deallocate memory for the temporary array
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            delete[] tempArr_blur[i][j];
        }

        delete[] tempArr_blur[i];
    }
    delete[] tempArr_blur;


}



//--------------------------------------------Function to apply 3D Convolution for Edge Detection

//3x3 Sobel kernel edgeDet_kernel for edge detection.
//This kernel is used to compute gradients in both the Xand Y directions.

void apply3DConvolutionEdgeDetection(int*** arr, int rows, int cols, Mat& edgeDetected) 
{
    // Defining a 3d blurring kernel
    //----------------------------------taking into account SOBEL TECHNIQUE

    int edgeDet_kernel[3][3] = {
        {-1, 0, 1}, 
        {-2, 0, 2},
        {-1, 0, 1} 
    };


    // logic for 3x3 convolution for edge detection
 // Applying the 3D convolution
 // Iterate over each pixel in the image
 //excluding the border pixels

    //rows
    for (int i = 1; i < rows - 1; i++) 
    {
        //cols
        for (int j = 1; j < cols - 1; j++) 
        {
            //vars
            int xaxis_sum = 0,yaxis_sum = 0;
           
            // Iterate over the 3x3 kernel
            //kernel rows
            for (int k = -1; k <= 1; k++) 
            {
                //kernel cols
                for (int l = -1; l <= 1; l++) 
                {
                    int store1 = edgeDet_kernel[k + 1][l + 1];
                    int store2 = edgeDet_kernel[l + 1][k + 1];

                    // Convolution in X direction
                    xaxis_sum += arr[i + k][j + l][0] * store1; 

                    // Convolution in Y direction
                    yaxis_sum += arr[i + k][j + l][0] * store2; 
                }
            }
            
            // Calculate the magnitude of the gradient using the Sobel operator
            
            int store3 = (xaxis_sum * xaxis_sum + yaxis_sum * yaxis_sum);

            // Magnitude = sqrt(sumX^2 + sumY^2)
            edgeDetected.at<uchar>(i, j) = saturate_cast<uchar>(sqrt(store3));
        }
    }
}




//-------------------------------------------- Function to apply 3D Convolution for Edge Detection
void apply3DConvolutionFeatureExtraction(int*** arr, int rows, int cols)
{
    // Defining a 3d feature extracting kernel
    int featureExt_kernel[3][3] = {
        {0, 1, 0},
        {1, -4, 1},
        {0, 1, 0} 
    };

    //temporary array to store the extracted image
    int*** tempArr_feature = new int** [rows];
    for (int i = 0; i < rows; ++i)
    {
        //allocations
        tempArr_feature[i] = new int* [cols];
        for (int j = 0; j < cols; ++j)
        {
            // Allocating memory for each channel in the pixel
           // Only considering one channel --- grayscale img
            tempArr_feature[i][j] = new int[1]; 
        }
    }

    // Applying the 3D convolution
   // Iterate over each pixel in the image
   //excluding the border pixels

    //rows
    for (int i = 1; i < rows - 1; i++)
    {
        //cols
        for (int j = 1; j < cols - 1; j++)
        {
            //var
            int sum = 0;

            // Iterate over the 3x3 kernel centered around the current pixel
            //kernel rows
            for (int k = -1; k <= 1; k++)
            {
                //kernel cols
                for (int m = -1; m <= 1; m++)
                {
                    //Multiply the pixel intensity with the corresponding kernel value
                    sum += arr[i + k][j + m][0] * featureExt_kernel[k + 1][m + 1]; // Convolution
                }
            }

            // Store the result in the feature-extracted array
          // Saturate the result to fit into the 8-bit unsigned char range
            tempArr_feature[i][j][0] = saturate_cast<uchar>(abs(sum)); 
        }
    }

    // Copy the edge-detected array back to the original array
    for (int i = 1; i < rows - 1; ++i)
    {
        for (int j = 1; j < cols - 1; ++j)
        {
            // Assign the blurred pixel value from the temporary array to the 
           //corresponding position in the original array
            arr[i][j][0] = tempArr_feature[i][j][0];
        }
    }

    // Deallocate memory for the temporary array
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            delete[] tempArr_feature[i][j];
        }

        delete[] tempArr_feature[i];
    }

    delete[] tempArr_feature;
}


