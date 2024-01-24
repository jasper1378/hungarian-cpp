/* vim: set filetype=cpp : */

#include "arg_parser.hpp"

#include <cstddef>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

hungarian_cpp::ArgParser::ArgParser(const int argc, char **argv,
                                    const std::vector<ValidName> &valid_names)
    : m_valid_names{valid_names} {
  Init(argc, argv);
}

hungarian_cpp::ArgParser::ArgParser(const int argc, char **argv,
                                    std::vector<ValidName> &&valid_names)
    : m_valid_names{std::move(valid_names)} {
  Init(argc, argv);
}

hungarian_cpp::ArgParser::ArgParser(const ArgParser &ap)
    : m_args{ap.m_args}, m_valid_names{ap.m_valid_names} {}

hungarian_cpp::ArgParser::ArgParser(ArgParser &&ap) noexcept
    : m_args{std::move(ap.m_args)}, m_valid_names{std::move(ap.m_valid_names)} {
}

hungarian_cpp::ArgParser::~ArgParser() {}

bool hungarian_cpp::ArgParser::ArgExists(const std::string_view name) const {
  for (size_t cur_arg{0}; cur_arg < m_args.size(); ++cur_arg) {
    if ((name == m_args[cur_arg].name.short_name) ||
        (name == m_args[cur_arg].name.long_name)) {
      return true;
    }
  }

  return false;
}

std::string
hungarian_cpp::ArgParser::GetValue(const std::string_view name) const {
  for (size_t cur_arg{0}; cur_arg < m_args.size(); ++cur_arg) {
    if ((name == m_args[cur_arg].name.short_name) ||
        (name == m_args[cur_arg].name.long_name)) {
      return m_args[cur_arg].value;
    }
  }

  return "";
}

hungarian_cpp::ArgParser &
hungarian_cpp::ArgParser::operator=(const ArgParser &ap) {
  m_args = ap.m_args;
  m_valid_names = ap.m_valid_names;

  return *this;
}

hungarian_cpp::ArgParser &
hungarian_cpp::ArgParser::operator=(ArgParser &&ap) noexcept {
  if (this == &ap) {
    return *this;
  }

  m_args = std::move(ap.m_args);
  m_valid_names = std::move(ap.m_valid_names);

  return *this;
}

void hungarian_cpp::ArgParser::Init(const int argc, char **argv) {
  for (char **cur_arg_ptr{argv + 1}; cur_arg_ptr != (argv + argc);
       ++cur_arg_ptr) {
    const std::string cur_arg{*cur_arg_ptr};

    bool arg_matches_a_valid_name{false};

    for (size_t cur_valid_name{0}; cur_valid_name < m_valid_names.size();
         ++cur_valid_name) {
      if ((cur_arg == m_valid_names[cur_valid_name].name.short_name) ||
          (cur_arg == m_valid_names[cur_valid_name].name.long_name)) {
        arg_matches_a_valid_name = true;

        if (m_valid_names[cur_valid_name].needs_value == false) {
          m_args.push_back({m_valid_names[cur_valid_name].name, ""});
          break;
        } else {
          if ((cur_arg_ptr + 1) != (argv + argc)) {
            for (size_t comparison_valid_name{0};
                 comparison_valid_name < m_valid_names.size();
                 ++comparison_valid_name) {
              if (((static_cast<std::string>(*(cur_arg_ptr + 1)) ==
                    m_valid_names[comparison_valid_name].name.short_name)) ||
                  ((static_cast<std::string>(*(cur_arg_ptr + 1)) ==
                    m_valid_names[comparison_valid_name].name.long_name))) {
                throw std::runtime_error{std::string{} + "Option: " + cur_arg +
                                         " is missing required argument, try "
                                         "\"hungarian-cpp --help\""};
                break;
              }
            }

            m_args.push_back({m_valid_names[cur_valid_name].name,
                              static_cast<std::string>(*(cur_arg_ptr + 1))});
            ++cur_arg_ptr;
            break;
          } else {
            throw std::runtime_error{
                std::string{} + "Option: " + cur_arg +
                " is missing required argument, try \"hungarian-cpp "
                "--help\""};
            break;
          }
        }
      }
    }

    if (arg_matches_a_valid_name == false) {
      throw std::runtime_error{std::string{} + "Incorrect option: " + cur_arg +
                               ", try \"hungarian-cpp --help\""};
    }
  }
}

std::ostream &hungarian_cpp::operator<<(std::ostream &out,
                                        const ArgParser &ap) {
  for (size_t cur_arg{0}; cur_arg < ap.m_args.size(); ++cur_arg) {
    out << "Short name: " << ap.m_args[cur_arg].name.short_name << '\n';
    out << "Long name: " << ap.m_args[cur_arg].name.long_name << '\n';
    out << "Value: "
        << ((ap.m_args[cur_arg].value.empty() == true)
                ? ("arg does not need a value")
                : (ap.m_args[cur_arg].name.short_name))
        << '\n';
    out << '\n';
  }

  return out;
}

