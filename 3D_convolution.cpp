//////Umama Bajwa
//////i221133 DATA C
//////q3 A1
//////cpp file 
////
////
////
////#include <opencv2/core.hpp>
////#include <opencv2/imgcodecs.hpp>
////#include <opencv2/highgui.hpp>
////#include <iostream>
////#include"3D_convolution.h"
////using namespace cv;
////using namespace std;
////
////
////
//////CV_8UC1 is used to define a single-channel matrix where each pixel value is an unsigned 8bit integer
//////used for grayscale imgs
////
//////---------- main ftn starts here
////int main()
////{
////    //obj
////    Mat img;
////
////    //----------------------------------------Loading the grayscale image
////
////    img = imread("C:/Users/DELL/OneDrive/Desktop/Data STructures/Project1/image-2.tiff", IMREAD_GRAYSCALE);
////
////    //validation
////    if (img.empty())
////    {
////        cout << "Could not open or find the image!" << endl;
////        return -1;
////    }
////
////
////    // Print the dimensions of the image
////    cout << "..............................................." << endl;
////    cout << "                IMAGE DIMENSIONS               " << endl;
////    cout << "..............................................." << endl << endl;
////    cout << "Image rows: " << img.rows << endl;
////    cout << "Image columns: " << img.cols << endl;
////
////    int img_rows = img.rows, img_cols = img.cols;
////
////    //-------------------------------------Dynamically allocate memory for the 3D array
////
////    int*** arr = new int** [img_rows];
////    for (int i = 0; i < img_rows; ++i)
////    {
////        arr[i] = new int* [img_cols];
////
////        for (int j = 0; j < img_cols; ++j)
////        {
////            // Only one channel -- grayscale img
////            arr[i][j] = new int[1];
////        }
////    }
////
////    //--------------------------------------- ftn call for storing 3d img
////    store3DImage(img, arr);
////
////
////    //---------------------------------------- naming & producing windows
////    namedWindow("Grayscale Image", WINDOW_AUTOSIZE);
////    namedWindow("Blurred Image", WINDOW_AUTOSIZE);
////    namedWindow("Edge-detected Image", WINDOW_AUTOSIZE);
////    namedWindow("Feature-Extracted Image", WINDOW_AUTOSIZE);
////
////
////    //------- Display the grayscale image
////    imshow("Grayscale Image", img);
////
////    //------------------------------------ BLURRING IMG logic STATR HERE
////
////        //ftn call
////    apply3DConvolution(arr, img_rows, img_cols);
////
////    // obj for blurred img
////    Mat blurImg(img_rows, img_cols, CV_8UC1);
////
////    for (int i = 0; i < img_rows; ++i)
////    {
////        for (int j = 0; j < img_cols; ++j)
////        {
////            // Assign the intensity value of the pixel from the 3D array to the corresponding position in the Mat object
////            blurImg.at<uchar>(i, j) = arr[i][j][0];
////        }
////    }
////
////    //displaying in window
////    imshow("Blurred Image", blurImg);
////
////    //storing as png
////    imwrite("Blurred Image.png", blurImg);
////
////    //------------------------------------ BLURRING IMG logic ends HERE
////
////
////
////
////
////    //------------------------------------Edge Detected IMG logic satrs HERE
////
////       // obj for storing edge det img
////    Mat edgeDetected(img_rows, img_cols, CV_8UC1);
////
////    // ftn call
////    apply3DConvolutionEdgeDetection(arr, img_rows, img_cols, edgeDetected);
////
////    // Display the edge-detected image
////    Mat edgeDet(img_rows, img_cols, CV_8UC1);
////
////    for (int i = 0; i < img_rows; ++i)
////    {
////        for (int j = 0; j < img_cols; ++j)
////        {
////            // Assign the intensity value of the pixel from the 3D array to the corresponding position in the Mat object
////            edgeDet.at<uchar>(i, j) = arr[i][j][0];
////        }
////    }
////
////    //displaying in window
////    imshow("Edge-detected Image", edgeDetected);
////
////    //storing as png file
////    imwrite("EdgeDetectedImage.png", edgeDetected);
////    //------------------------------------Edge Detected IMG logic ends HERE
////
////
////
////
////    //------------------------------------ feature extraction IMG logic starts HERE
////
////       // ftn call
////    apply3DConvolutionFeatureExtraction(arr, img_rows, img_cols);
////
////    // obj & display
////    Mat featureEx(img_rows, img_cols, CV_8UC1);
////
////    for (int i = 0; i < img_rows; ++i)
////    {
////        for (int j = 0; j < img_cols; ++j)
////        {
////            // Assign the intensity value of the pixel from the 3D array to the corresponding position in the Mat object
////            featureEx.at<uchar>(i, j) = arr[i][j][0];
////        }
////    }
////
////    //display in window
////    imshow("Feature-Extracted Image", featureEx);
////
////    //saving as png 
////    imwrite("FeatureExtractedImage.png", featureEx);
////    //------------------------------------ feature extraction IMG logic sends HERE
////
////
////
////       // Wait for a key press to exit
////    waitKey(0);
////
////    // Close all windows
////    destroyAllWindows();
////
////
////
////    //-------------------- deallocation 
////
////    for (int i = 0; i < img_rows; ++i)
////    {
////        for (int j = 0; j < img_cols; ++j)
////        {
////            delete[] arr[i][j];
////        }
////
////        delete[] arr[i];
////    }
////
////    delete[] arr;
////
////    return 0;
////}