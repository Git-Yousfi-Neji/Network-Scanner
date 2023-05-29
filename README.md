
# Network Scanner

This is a simple network scanner implemented in C that allows you to scan a range of IP addresses and check for open ports on each device.

## Features

- Scans a specified IP for open ports
- Prints the open port numbers
- Basic error handling for invalid inputs

## Prerequisites

- GCC compiler
- C99 standard

## Usage

- Clone the repository:

```
git clone https://github.com/Git-Yousfi-Neji/Network-Scanner.git
```

- Navigate to the project directory:

```
cd Network-Scanner
```

- Compile the project:

```
make
```

- Run the network scanner:

```
./scanner
```

- Enter the IP range to scan when prompted.

- The program will perform the network scan and display the IP addresses and open ports found.

- Once the scan is complete, the program will terminate.

## Example
```
Enter IP range to scan: 192.168.1.1-192.168.1.3
Enter IP Start: 77
Enter IP End: 81
Performing network scan...
Scanning IP: 192.168.1.1
Trying with port: 77
Trying with port: 78
Trying with port: 79
Trying with port: 80
Port 80 open
Trying with port: 81
Scanning IP: 192.168.1.2
Trying with port: 77
Trying with port: 78
Trying with port: 79
Trying with port: 80
Trying with port: 81
Scanning IP: 192.168.1.3
Trying with port: 77
Trying with port: 78
Trying with port: 79
Trying with port: 80
Trying with port: 81
Network scan completed.
Scan Completed.
```
## Contribution

Contributions to this project are welcome. Feel free to fork the repository, make improvements, and submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
## Several enhancement TODO

- [x] Multithreading: Implement multithreading to improve the scanning speed by scanning multiple IP addresses or ports concurrently.

- [x] Port Range Configuration: Allow the user to specify a custom port range to scan instead of scanning all ports from 1 to 65535.

- [ ] Service Detection: Enhance the scanner to identify the specific services running on open ports by performing service fingerprinting or banner grabbing.

- [ ] Error Handling: Implement more comprehensive error handling to handle network errors, connection timeouts, or invalid user inputs gracefully.

- [x] Output Formatting: Improve the output formatting to make the scan results more readable and informative.

- [ ] Network Range Parsing: Extend the IP range parsing capability to handle more complex IP range formats, such as CIDR notation or wildcard masks.

- [ ] Operating System Detection: Integrate operating system detection capabilities to identify the operating system running on each scanned device based on network fingerprinting techniques.

- [ ] Input Validation: Implement input validation to ensure that the user-provided IP range is in a valid format and perform error handling for incorrect inputs.

- [ ] Logging: Add logging functionality to record the scan results and any relevant information, allowing for later analysis or troubleshooting.

- [ ] Integration with Database: Provide an option to store the scan results in a database for further analysis, historical tracking, or integration with other tools.

- [x] Command-Line Options: Implement command-line options to customize the scanning behavior, such as specifying the timeout duration, enabling verbose output, or choosing scan techniques.

- [ ] Host Discovery: Include host discovery techniques to identify live hosts within a given IP range before performing port scanning, reducing unnecessary scanning on inactive hosts.
