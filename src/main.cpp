#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

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

struct {
    string* path;
    string* output_path;
} cli_arguments;

const auto get_cli_arguments(int n_args, const char** v_args) {
    string* raw_arguments[n_args - 1];

    for (uint8_t i = 0; i < n_args - 1; i++) {
        raw_arguments[i] = new string(v_args[i + 1]);
        //cout << *raw_arguments[i] << " ";
    }

    cli_arguments.path = raw_arguments[0];

    return &cli_arguments;
}

int main(int n_args, const char** v_args) {
    const auto args = get_cli_arguments(n_args, v_args);
    cout << "\n" << *args->path;
    return 0;
}