#include "TFLiteDetector.h"

TFLiteDetector::~TFLiteDetector()
{
    if (tf_lite_model != nullptr)
        TfLiteModelDelete(tf_lite_model);
}

std::vector<tBoundingBox> TFLiteDetector::Detect(cv::Mat& src)
{
    std::vector<tBoundingBox> detections;
    int width = src.cols;
    int height = src.rows;

    cv::Mat image = Normalize_Source_Mat(src);
    int status = Invoke_Graph(image);

    if (status == 0) {
        const float* detection_locations = output_locations->data.f;
        const float* detection_classes = output_locations->data.f;
        const float* detection_scores = output_scores->data.f;
        int nr_of_detections = (int)*num_detections->data.f;

        detections.reserve(nr_of_detections);
        for (int i = 0; i < nr_of_detections; i++) {

            tBoundingBox bounding_box;
            bounding_box.confidence = detection_scores[i];

            if (bounding_box.confidence > this->confidence_threshold) {
                bounding_box.id = int(detection_classes[i]);
                bounding_box.label = labels[bounding_box.id];
                bounding_box.roi.y = detection_locations[i * 4] * height;
                bounding_box.roi.x = detection_locations[i * 4 + 1] * width;
                bounding_box.roi.height = (detection_locations[i * 4 + 2] * height) - bounding_box.roi.y;
                bounding_box.roi.width = (detection_locations[i * 4 + 3] * width) - bounding_box.roi.x;

                detections.emplace_back(bounding_box);
                Draw_Bounding_Box(src, bounding_box);
            }
        }
    }
    return detections;
}

void TFLiteDetector::Init_Model()
{
    //Step 1: Load the model
    tf_lite_model = TfLiteModelCreateFromFile(model_path);
    if (tf_lite_model == nullptr) {
        printf("Failed to load the model \n");
    }

    //Init the interpreter for the graph
    //Might be worth experimenting with multiple threads here but for the sake of stability I'll leave it as 1
    TfLiteInterpreterOptions* options = TfLiteInterpreterOptionsCreate();
    TfLiteInterpreterOptionsSetNumThreads(options, 1);

    this->interperter = TfLiteInterpreterCreate(tf_lite_model, options);
    if (this->interperter == nullptr) {
        printf("Failed to create the interpreter \n");
    }

    //Init the input and output tensors of the model
    this->input_tensor = TfLiteInterpreterGetInputTensor(interperter, 0);
    this->output_locations = TfLiteInterpreterGetOutputTensor(interperter, 0);
    this->output_classes = TfLiteInterpreterGetOutputTensor(interperter, 1);
    this->output_scores = TfLiteInterpreterGetOutputTensor(interperter, 2);
    this->num_detections = TfLiteInterpreterGetOutputTensor(interperter, 3);

    if (TfLiteInterpreterAllocateTensors(interperter) != kTfLiteOk) {
        printf("Failed to allocate memory for the tensors \n");
    }

    if (Validate_Detection_Model() == 0) {
        printf("Loaded model from: %s", this->model_path);
    } else {
        printf("Failed to intialize model");
    }
}

void TFLiteDetector::Load_Labels()
{
    std::ifstream names(this->label_path);
    std::string cls;
    while (getline(names, cls)) {
        this->labels.emplace_back(cls);
    }
    printf("Loaded labels from: %s", this->label_path);
}

int TFLiteDetector::Validate_Detection_Model()
{
    if (TfLiteInterpreterGetInputTensorCount(interperter) != 1) {
        printf("Detection model should only have 1 input tensor \n");
        return -1;
    }
    if (this->model_quantized && input_tensor->type != kTfLiteUInt8) {
        printf("Model is quantized but the input type is not an 8 bit int \n");
    }
    if (!this->model_quantized && input_tensor->type != kTfLiteFloat32) {
        printf("Model is not quantized but the input type is not a 32 bit float \n");
    }
    if (this->input_tensor->dims->data[0] != 1 || this->input_tensor->dims->data[1] != detection_model_size || this->input_tensor->dims->data[2] != detection_model_size || this->input_tensor->dims->data[3] != DETECTION_MODEL_CNLS) {
        printf("Detection model size does not match the size of the graph");
        return -1;
    }
    if (TfLiteInterpreterGetOutputTensorCount(interperter) != 4) {
        printf("Detection model should have 4 output tensors \n");
        return -1;
    }
    return 0;
}

int TFLiteDetector::Invoke_Graph(cv::Mat src)
{
    if (model_quantized) {
        uchar* dst = this->input_tensor->data.uint8;
        // Copy image into input tensor
        memcpy(dst, src.data, sizeof(uchar) * detection_model_size * detection_model_size * DETECTION_MODEL_CNLS);
    } else {
        // Normalize the image so each pixel is between -1 to 1
        src.convertTo(src, CV_32FC3, 2.0 / 255.0, -1.0);
        // Copy image into input tensor
        float* dst = input_tensor->data.f;
        memcpy(dst, src.data,
            sizeof(float) * detection_model_size * detection_model_size * DETECTION_MODEL_CNLS);
    }

    //Invoke the model
    if (TfLiteInterpreterInvoke(this->interperter) != kTfLiteOk) {
        printf("Error invoking the detection model \n");
        return -1;
    }
    return 0;
}

cv::Mat TFLiteDetector::Normalize_Source_Mat(cv::Mat src)
{
    //Resize the mat to the input size of the model
    cv::Mat image;
    resize(src, image, cv::Size(detection_model_size, detection_model_size), 0, 0, cv::INTER_AREA);

    // Make sure the image has 3 channels
    int cnls = image.type();
    if (cnls == CV_8UC1) {
        cv::cvtColor(image, image, cv::COLOR_GRAY2RGB);
    } else if (cnls == CV_8UC3) {
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    } else if (cnls == CV_8UC4) {
        cv::cvtColor(image, image, cv::COLOR_BGRA2RGB);
    }

    return image;
}

//Draw a bounding box - Frame, bounding box
void TFLiteDetector::Draw_Bounding_Box(cv::Mat& mat, tBoundingBox bounding_box)
{
    int baseLine;
    std::string label = cv::format("%.2f", bounding_box.confidence);
    label = bounding_box.label + ":" + label;
    cv::Size label_size = getTextSize(label, cv::FONT_ITALIC, 0.5, 1, &baseLine);
    int top = std::max(bounding_box.roi.y, label_size.height);

    cv::rectangle(mat,
        cv::Point(bounding_box.roi.x, bounding_box.roi.y),
        cv::Point(bounding_box.roi.x + bounding_box.roi.width,
            bounding_box.roi.y + bounding_box.roi.height),
        cv::Scalar(0, 255, 0), 4);

    rectangle(mat,
        cv::Point(bounding_box.roi.x, bounding_box.roi.y - round(1.1 * label_size.height)),
        cv::Point(bounding_box.roi.x + round(1.1 * label_size.width), top + baseLine),
        cv::Scalar(0, 255, 0), cv::FILLED);

    cv::putText(mat, label, cv::Point(bounding_box.roi.x, top), cv::FONT_ITALIC, 0.5, cv::Scalar(0, 0, 0), 1);
}
