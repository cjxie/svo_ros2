#include "rclcpp/rclcpp.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/core.hpp"
#include <sensor_msgs/image_encodings.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/compressed_image.hpp>

#include "svo_interface.hpp"

namespace svo_ros2{
    class SvoNode : public rclcpp::Node
    {
    public:
        SvoNode();
        ~SvoNode();

        void initialize_interface();
    
    private:
        void CompressedImageCallback(const sensor_msgs::msg::CompressedImage::SharedPtr msg);
        void ImageCallback(const sensor_msgs::msg::Image::SharedPtr msg);
        
        std::string image_topic_, publish_topic_;
        bool use_compressed_image_;

        std::shared_ptr<SvoInterface> svo_interface_;

        rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr compressed_image_sub_;
        rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr image_sub_;

        rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr image_pub_;

    };
}
