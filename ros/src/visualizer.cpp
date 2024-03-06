#include "visualizer.hpp"


namespace svo_ros2
{
Visualizer::Visualizer(const rclcpp::Node::SharedPtr node, int n_cameras):
node_(node), n_cameras_(n_cameras)
{
    // initialize publishers
    image_pub_.resize(n_cameras);
    
    for (size_t i = 0; i < n_cameras; i++)
    {
        image_pub_.at(i) = node_->create_publisher<sensor_msgs::msg::Image>("camera" + std::to_string(i), 10);
    }
}

Visualizer::~Visualizer(){};


void Visualizer::publishImage(const std::vector<cv::Mat> &images, const int64 timestamp_nanoseconds)
{
    for (size_t i=0; i < images.size(); i++)
    {
        cv::Mat image;
        if (images.at(i).type() == CV_8UC1)
            // create pyramid
            image = images[i];
        else if (images.at(i).type() == CV_8UC3)
            cv::cvtColor(images.at(i), image, cv::COLOR_BGR2GRAY);
        else
            RCLCPP_ERROR(node_->get_logger(), "Unknown image type");

        

        cv_bridge::CvImage img_msg;
        img_msg.header.stamp = rclcpp::Time(timestamp_nanoseconds);
        img_msg.header.frame_id = "cam" + std::to_string(i);
        img_msg.encoding = "mono8";
        img_msg.image = image.clone();

        // sensor_msgs::msg::Image::SharedPtr img_msg = cv_bridge::CvImage(msg->header, "bgr8", image).toImageMsg();
        image_pub_.at(i)->publish(*img_msg.toImageMsg());
    }
}

}
