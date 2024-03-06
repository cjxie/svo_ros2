#include<rclcpp/rclcpp.hpp>

namespace svo_ros2
{

namespace factory
{

// Factory for Mono-SVO
std::shared_ptr<FrameHandlerMono> makeMono(
    const rclcpp::Node::SharedPtr node,
    const CameraBundlePtr & cam = nullptr);

} // namespace factory



} // namespace svo_ros2