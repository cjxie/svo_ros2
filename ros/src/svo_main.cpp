#include "svo_node.hpp"

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<svo_ros2::SvoNode>();
    
    node->initialize_interface();
    
    // RCLCPP_INFO(node->get_logger(), "Svo pipeline start");
    rclcpp::spin(node);
    // RCLCPP_INFO(node->get_logger(), "Svo pipeline end"); 

    rclcpp::shutdown();
    return 0;
}
