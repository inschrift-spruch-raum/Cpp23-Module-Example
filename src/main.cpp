import std;
import vulkan;

int main() {
    const vk::raii::Context ctx;

    constexpr vk::ApplicationInfo app_info{
        .pApplicationName = "My App",
        .applicationVersion = 1,
        .pEngineName = "My Engine",
        .engineVersion = 1,
        .apiVersion = vk::makeApiVersion(1, 4, 0, 0)
    };
    
    const vk::InstanceCreateInfo create_info{
        .pApplicationInfo = &app_info
    };
    
    auto [InstanceRes, instance] = ctx.createInstance(create_info);
    if (InstanceRes != vk::Result::eSuccess) {
        std::println("Failed to create Vulkan instance: {}", vk::to_string(InstanceRes));
        return -1;
    }

    std::println("Physical Device: ");

    auto [PhysicalDevicesRes, physicalDevices] = instance.enumeratePhysicalDevices();
    if (PhysicalDevicesRes != vk::Result::eSuccess) {
        std::println("Failed to enumerate physical devices: {}", vk::to_string(PhysicalDevicesRes));
        return -1;
    }

    for (const auto& physicalDevice : physicalDevices) {
        std::println("\t{}", std::string_view{ physicalDevice.getProperties().deviceName });
    }
}