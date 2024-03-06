#include<rclcpp/rclcpp.hpp>
#include<cv_bridge/cv_bridge.h>
#include<sensor_msgs/msg/compressed_image.hpp>
#include<sensor_msgs/msg/image.hpp>
#include<sensor_msgs/image_encodings.hpp>
#include "opencv2/core.hpp"
#include<vector>



namespace svo_ros2
{

// publish visualisation messages to ros
class Visualizer
{
    public:
        Visualizer(const rclcpp::Node::SharedPtr node, int n_cameras);
        ~Visualizer();
    
        void publishImage(const std::vector<cv::Mat> &images, const int64_t timestamp_nanoseconds);

    private:
        const rclcpp::Node::SharedPtr node_;
        size_t n_cameras_;

        std::vector<rclcpp::Publisher<sensor_msgs::msg::Image>:: SharedPtr> image_pub_;

};


} // namespace svo_ros2