#include "./tf-dependencies/c_api.h"
#include "./tf-dependencies/common.h"
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>

#define NON_QUANTIZED false
#define QUANTIZED true

typedef struct {
    int id;
    float confidence;
    cv::Rect roi; //Region of Interest
    float distance;
    std::string label;
} tBoundingBox;

class TFLiteDetector
{
    public:
        TFLiteDetector() = default;
        ~TFLiteDetector();
        std::vector<tBoundingBox> Detect(cv::Mat& frame);

        void Init_Model();
        void Load_Labels();

        const char* model_path;
        const char* label_path;
        std::vector<std::string> labels;
        int detection_model_size;
        float confidence_threshold;
        bool model_quantized = false;

    private:
        int Validate_Detection_Model();
        cv::Mat Normalize_Source_Mat(cv::Mat src);
        int Invoke_Graph(cv::Mat src);
        void Draw_Bounding_Box(cv::Mat& frame, tBoundingBox bounding_box);

        TfLiteModel* tf_lite_model;
        TfLiteInterpreter* interperter;

        //Input node
        TfLiteTensor* input_tensor = nullptr;

        //Output nodes
        const TfLiteTensor* output_locations = nullptr;
        const TfLiteTensor* output_classes = nullptr;
        const TfLiteTensor* output_scores = nullptr;
        const TfLiteTensor* num_detections = nullptr;


        const int DETECTION_MODEL_CNLS = 3;
        const float IMAGE_MEAN = 128.0;
        const float IMAGE_STD = 128.0;
};
