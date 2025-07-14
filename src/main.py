import sys

CliArguments_ERROR_NOT_ENOUGH = Exception("At least one argument must be specified")
CliArguments_ERROR_INPUT_MUST_BE_FIRST = Exception("Directory to scan must be the first argument")

USAGE_INSTRUCTION = """Usage:"""

class CliArguments:
    path = ""
    output_path = ""

def scan_cli_arguments():
    """
    directory to scan is always the first argument
    output_path is always the last argument
    """
    arguments = CliArguments()
    raw_args = sys.argv[1:]

    if len(raw_args) == 0:
        raise CliArguments_ERROR_NOT_ENOUGH

    if "=" not in raw_args[0]:
        arguments.path = raw_args[0]
    else:
        # first argument is not an input
        raise CliArguments_ERROR_INPUT_MUST_BE_FIRST
    
    if "=" not in raw_args[-1]:
        # last argument is output path
        arguments.output_path = raw_args[-1]

    # will be used to scan other arguments:
    # for raw_arg in raw_args[1:]:

    return arguments


def main():
    arguments = scan_cli_arguments()
    print(arguments.path, arguments.output_path)

if __name__ == "__main__":
    main()