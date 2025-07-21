//#include <iostream>
//#include <string>
//#include <cstdint>

#include "include/cli_arguments.hpp"
#include "include/recursive_scan.hpp"
#include "include/plantuml_schema.hpp"

//using namespace cli_arguments_ns;
//using namespace recursive_scan_ns;
//using namespace plantuml_schema_ns;

/*
 _   _                                          _                 _     ___ 
| \ | | ___    _ __   ___  _ __ _ __ ___   __ _| |   ___ ___   __| | __|__ \
|  \| |/ _ \  | '_ \ / _ \| '__| '_ ` _ \ / _` | |  / __/ _ \ / _` |/ _ \/ /
| |\  | (_) | | | | | (_) | |  | | | | | | (_| | | | (_| (_) | (_| |  __/_| 
|_| \_|\___/  |_| |_|\___/|_|  |_| |_| |_|\__,_|_|  \___\___/ \__,_|\___(_)

MMMMMMMMMMk          .....''''''''''''''''''''''''''''''''''''''''''''''''''''''''''',,,,,,'';MMMMMMMMMMMMMMMMMMM
MMMMMMMMMMo        ......'',,',,,,,''''''''''''''''''''''''''''''''''''''''''''''''',,;;;;;,,,WMMMMMMMMMMMMMMMMMM
MMMMMMMMMM:      ........',,,,,,,,,,,,,,,,,,,,,,,,,,''''''''''''''''''''''''''''',,,,;;;;;;;,,WMMMMMMMMMMMMMMMMMM
MMMMMMMMMM,     .........,,;;;,,;;;;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'''''''''''''',,;;;;;;;;,;MMMMMMMMMMMMMMMMMMM
MMMMMMMMMM'   ..........';;;;;;:::;;;;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,'''',,,,,,;;;;;;;;;;lMMMMMMMMMMMMMMMMMMM
MMMMMMMMMM.   ..........,;;;;:::::;;;;;;;;;;;;;;;;,;;;;;;;;;;;;;,,,,,,,,,,,,,,,,,;;;;:;;;;;;;kMMMMMMMMMMMMMMMMMMM
MMMMMMMMMM.    ....   ..;;;:ccc:;;;,;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;,,,,,,,,,,,,;;:::;;;;;;;:NMMMMMMMMMMMMMMMMMMM
MMMMMMMMMM'           .';:ccc:;;;,,,;;;;:::;;;;;;;;;;;;;;;;;;;;;;;;;;,,,,,,,,;;;;;;::::;;;;;xMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMx      .oXWx.;:c::;;;;,,,,,,;;:::::::::;;;;;;:::::::::;;;;;;;;;;,;;;;;;::::::;;;;cWMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMk.   :NMMM0;;;;;;;;,,,,,,',,,;::::::::::;;;;;;;::::ccccc:::;;;;;;;;;::::::::;;::XMMMMMMMMMMMMMMMMMX0MM
MMMMMMMMMMMMN: lMMMMMk;;;;;,,,,''....',,,,;::::::::;;;;;;;;;::::cccccc::::::::::::::::::::KMMMMMMMMMMMMMMKo,.'dMM
MMMMMMMMMMMMMM0KMMMMM:.........   ...,,,,'..,;;;;;;;;;;;;;;;;;:::::cccc::::cccccc::::::::OMMMMMMMMMMMXxc.,o0WMMMM
MMMMMMMMMMMMMMMMMMMMK          ...',,,,,,,,....',,;;;;;;;;;;;;;;;;;:::::ccccccccc:::;;::dMMMMMMMMWOc'.lkNMMMMMMMM
MMMMMMMMMMMMMMMMMMMMWl.  ...''',,,,,;;;;;,,,,'.................'',,;;;:cccllllcc::;;;;:lWMMMMMXx:.:dKWMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMWk,.,,,,,,,,,,,,,;;;;,,,,,'....          ....',;;:clllllc:;;;;;:dWMMMKl.'dKMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMO:',,,,,,,,,,,,,;;,,,,,,,,,,''....       ...',::clllc:;;;;;l0MMXl..lKMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMNd'.,,'..''',,,;;,,,,,,,,,,,,,,,,,'.... ...';:cllc:;,;lkXMWx;.lKMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMWc  .'.   .',;;,',,'''''''''',,,,,,,,'....,:clc:;o0WMWk;.cKMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMW.:ol.   . .;;,'''''..........''',,,,,,'.,:cc:;:00xl. :NMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMcoo,.  .. .;,''''....''.      ..''''''',;cl:,'..''.,OMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMN0d'';,...   ';,''''..;ll.  ..     ..'''',;cl:'.''..;OMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMW0o,   ,;,'......,:;,''''..cl;.  ..   '. .;;;;:cl;.....:KMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMWKx;       ':;,,,,;;::;,''''...,cc'......':,.;cllooo::lodONMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMW:...        .;;;;;::::,''''''......'......'',:llooooxXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMM0l,..........,;;;:::;,,''''''''''.......'',::clllldXMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMWx. ..    .;:cc:;,,,,,,,,,'',,,,,,,,,,,;;;::::OMMNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMN.......;:cc:;;;::::;;,,,,,,,''''''''',,;;:;',...kMMMMMMMMMMNMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMM;.....:cc:::cclllllc:;;;,''''''''''',,;;:,':'....:ldxxkkdcl.WMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMX. ...;cccccloddddolcc:::,''''''''',,;;::'  ...........  ... dMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMWx.  ..;clllooddddddllcc:;,''.''''',,;;:cc.       ..............:OWMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMk.   .,::lloodddddooc:;;;;,,,'''''',;;:cc:.            .............;lkNMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMl      .',;:cllllc::::ccllllc:;,''',;;:cc;                      .......  .:kWMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMW:        ...'',,,,'',;:ccclllllc:,'',;:c:.                                    :0MMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMW,             .,'......',;:cc;;;::,'';::;.                                       '0MMMMMMMMMMMMM
MMMMMMMMMMMMMMMMl              .,'.   ...''',;;::,,,',;;'....                                       ,XMMMMMMMMMMM
*/

/*
    Basic workflow:
    Create code for plantuml, write it to the stdout
*/

int main(int n_args, const char** v_args) {
    try {
        cli_arguments_ns::CliArguments& args = cli_arguments_ns::get_cli_arguments(n_args, v_args);
        vector<recursive_scan_ns::FilesystemEntry>& seq = recursive_scan_ns::scan(*args.path);
        plantuml_schema_ns::create_schema(seq, args);
    } catch(const exception& exp) {
        // gracefully exiting with error
        cerr << exp.what() << endl;
        return 1;
    }
    return 0;
}