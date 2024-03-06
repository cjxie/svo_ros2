#include "svo_node.hpp"

using std::placeholders::_1;

namespace svo_ros2 {
    
SvoNode::SvoNode()
: Node("svo_ros2")
{   
    this->declare_parameter("pipeline_type", static_cast<int>(PipelineType::kMono));
}



SvoNode::~SvoNode(){};

// (todo) replace with a image subscriber thread
void SvoNode::initialize_interface()
{
    PipelineType pipeline_type= static_cast<PipelineType>(this->get_parameter("pipeline_type").as_int());
    // create a sharePtr outside the constructor otherwise an unfully constructed pointer will lead to issue.  
    svo_interface_ = std::make_shared<SvoInterface>(shared_from_this(), pipeline_type);
        
    svo_interface_->subscribeImage();
}


void SvoNode::CompressedImageCallback(const sensor_msgs::msg::CompressedImage::SharedPtr msg)
{
    cv::Mat image;
    try
    {
        image = cv_bridge::toCvCopy(msg, "bgr8")->image;
    }
    catch(const std::exception& e)
    {
        RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        return;
    }
    
    // perform tracking task on the image

    // publish the result
    sensor_msgs::msg::Image::SharedPtr pub_image = cv_bridge::CvImage(msg->header, "bgr8", image).toImageMsg();
    image_pub_->publish(*pub_image);
}

// not implement yet
void ImageCallback(const sensor_msgs::msg::Image::SharedPtr msg)
{

    return;
}


}


