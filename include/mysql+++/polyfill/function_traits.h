#pragma once

#include <tuple>
#include <type_traits>

namespace sqlite
{
    namespace utility
    {

        template <typename>
        struct function_traits;

        template <typename Function>
        struct function_traits : public function_traits<
                                     decltype(&std::remove_reference<Function>::type::operator())>
        {
        };

        template <
            typename ClassType,
            typename ReturnType,
            typename... Arguments>
        struct function_traits<
            ReturnType (ClassType::*)(Arguments...) const>
        {
            using result_type = ReturnType;

            template <std::size_t Index>
            using argument = typename std::tuple_element<
                Index,
                std::tuple<Arguments...>>::type;

            static const std::size_t arity = sizeof...(Arguments);
        };

        /* support the non-const operator ()
     * this will work with user defined functors */
        template <
            typename ClassType,
            typename ReturnType,
            typename... Arguments>
        struct function_traits<
            ReturnType (ClassType::*)(Arguments...)>
        {
            using result_type = ReturnType;

            template <std::size_t Index>
            using argument = typename std::tuple_element<
                Index,
                std::tuple<Arguments...>>::type;

            static const std::size_t arity = sizeof...(Arguments);
        };

    } // namespace utility
} // namespace sqlite
