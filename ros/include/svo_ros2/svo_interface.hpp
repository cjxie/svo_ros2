#include<rclcpp/rclcpp.hpp>
#include<cv_bridge/cv_bridge.h>
#include<sensor_msgs/msg/compressed_image.hpp>
#include<sensor_msgs/msg/image.hpp>
#include<sensor_msgs/image_encodings.hpp>
#include "opencv2/core.hpp"
#include<vector>

#include "visualizer.hpp"


/*
        SvoInterface
This class handles the background tasks or processing look
*/

namespace svo_ros2
{

enum class PipelineType
{
    kMono,
    kStereo,
    kArray
};

    class SvoInterface
    {
        public:

            SvoInterface(rclcpp::Node::SharedPtr node,  const PipelineType pipeline_type);
            virtual ~SvoInterface();

            rclcpp::Node::SharedPtr node_;
            PipelineType pipeline_type_;
            size_t n_camera_ ;
            // image thread
            std::shared_ptr<std::thread> image_thread_;
           
            rclcpp::Subscription<sensor_msgs::msg::CompressedImage>::SharedPtr compressed_image_sub_;
            
          
            // svo modules
            std::shared_ptr<Visualizer> visualizer_;
            
            // procces whole svo pipeline
            void processImageBundle(const std::vector<cv::Mat> &images, const int64_t timestamp_nanoseconds);
            
            // publish results to ros
            void publishResults(const std::vector<cv::Mat> &images, const int64_t timestamp_nanoseconds);

            // Subscribe CompressedImage
            void CompressedCallback(const sensor_msgs::msg::CompressedImage::SharedPtr msg);

            void subscribeImage();

            void monoLoop();

        private:
            


    };
    
} // namespace svo_ros2

