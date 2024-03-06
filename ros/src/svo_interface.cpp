#include "svo_interface.hpp"


namespace  svo_ros2
{

SvoInterface::SvoInterface(rclcpp::Node::SharedPtr node,  const PipelineType pipeline_type)
:node_(node), pipeline_type_(pipeline_type)
{
    switch (pipeline_type)
    {
        case PipelineType::kMono:
            // std::cout<<"Using Mono vo"<< std::couit
            RCLCPP_INFO(node_->get_logger(), "Using mono");
            n_camera_ = 1;
            // vo_ = ;
            break;
        case PipelineType::kStereo:
            // vo_ = ; 
            RCLCPP_INFO(node_->get_logger(), "Using stereo");
            n_camera_ = 2;
            break;
        case PipelineType::kArray:
            // vo_ = ;
            RCLCPP_INFO(node_->get_logger(), "Using multiple cameras");
            break;
        default:
            RCLCPP_ERROR(node_->get_logger(), "no camera found");
            break;
    }

    // start the visualizer to publish results
    RCLCPP_INFO(node_->get_logger(), "Start visualizer");
    visualizer_ = std::make_shared<Visualizer>(node_, n_camera_);
    //(todo) get parameters here

    // ready to start the whole pipeline

}

SvoInterface::~SvoInterface()
{
    if (image_thread_)
    image_thread_->join();
    RCLCPP_INFO(node_->get_logger(), "vo destructed");
}

void SvoInterface::processImageBundle(
    const std::vector<cv::Mat>& images,
    const int64_t timestamp_nanoseconds)
{
    // vo_->addImageBundle(images, timestamp_nanoseconds);
}


void SvoInterface::publishResults(const std::vector<cv::Mat> &images, const int64_t timestamp_nanoseconds)
{
    //(todo) implement a visualizer class under svo_ros2 namespacee
    // handling all the publish staff
    visualizer_->publishImage(images, timestamp_nanoseconds);

}


void SvoInterface::CompressedCallback(const sensor_msgs::msg::CompressedImage::SharedPtr msg)
{
    cv::Mat image;
    try
    {
        image = cv_bridge::toCvCopy(msg, "bgr8")->image;
    }
    catch(const std::exception& e)
    {
        RCLCPP_ERROR(node_->get_logger(), "cv_bridge exception: %s", e.what());
        return;
    }
    std::vector<cv::Mat> images;
    images.push_back(image.clone());
    
    // start the whole process here 
    // perform tracking task on the image
    
    processImageBundle(images, msg->header.stamp.nanosec);

    // publish the result
    publishResults(images, msg->header.stamp.nanosec);

}

void SvoInterface::monoLoop()
{
    // auto node = std::make_shared<rclcpp::Node>("loop node");
    RCLCPP_INFO(node_->get_logger(), "SvoNode started Image loop");
    std::string image_topic = "/camera/panoramic/image/compressed";
    
    compressed_image_sub_= node_->create_subscription<sensor_msgs::msg::CompressedImage>(
        image_topic,
        10,
        // [this](sensor_msgs::msg::CompressedImage::SharedPtr msg){SvoInterface::CompressedCallback(msg);});
        std::bind(&SvoInterface::CompressedCallback, this, std::placeholders::_1));
    RCLCPP_INFO(node_->get_logger(), "Receive images from %s", image_topic.c_str());
}


void SvoInterface::subscribeImage()
{   
    // The thread is tasked with executing the monoLoop member function on the this object, 
    // indicating it's operating on the current instance of SvoInterface
    if(pipeline_type_ == PipelineType::kMono)
        image_thread_ = std::unique_ptr<std::thread>(new std::thread(&SvoInterface::monoLoop, this));
    else if(pipeline_type_ == PipelineType::kStereo)
        std::cout<< "stereo is not implemented" <<std::endl;
    // image_thread_ = std::unique_ptr<std::thread>(
    //     new std::thread(&SvoInterface::stereoLoop, this));
}


} // namespace svo_ros2