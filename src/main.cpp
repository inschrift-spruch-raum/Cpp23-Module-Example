import std;

template<typename T>
concept Addable = requires(const T& lhs, const T& rhs) {
    { lhs + rhs } -> std::same_as<T>;
};

auto add(Addable auto const& lhs, Addable auto const& rhs) {
    return lhs + rhs;
}

int main()
{
    std::string s = "Hello C++23 import std!\n";
    std::string_view s_view = s;
    std::print("{}", s_view);

    std::println("1 + 1 = {}", add(1, 1));
}