/* vim: set filetype=cpp : */

#ifndef ARG_PARSER_HPP
#define ARG_PARSER_HPP

#include <iostream>
#include <string>
#include <vector>

class ArgParser {
public:
  struct ArgName {
    std::string short_name{};
    std::string long_name{};
  };

  struct ValidName {
    ArgName name{};
    bool needs_value{};
  };

private:
  struct Arg {
    ArgName name{};
    std::string value{};
  };

public:
  ArgParser(const int argc, char **argv,
            const std::vector<ValidName> &valid_names);
  ArgParser(const int argc, char **argv, std::vector<ValidName> &&valid_names);

  ArgParser(const ArgParser &ap);
  ArgParser(ArgParser &&ap) noexcept;

  ~ArgParser();

private:
  std::vector<Arg> m_args;

  std::vector<ValidName> m_valid_names;

public:
  bool ArgExists(const std::string &name) const;

  std::string GetValue(const std::string &name) const;

public:
  ArgParser &operator=(const ArgParser &ap);
  ArgParser &operator=(ArgParser &&ap) noexcept;

  friend std::ostream &operator<<(std::ostream &out, const ArgParser &ap);

private:
  void Init(const int argc, char **argv);
};

#endif
