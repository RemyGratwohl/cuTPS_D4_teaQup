# COMP3004A: cuTPS Project
==========================

**Fall 2014 (September - December)**

### Authors
- Analee Chicot, ID: 100822791
- Remy Gratwohl, ID: 100891970
- Brandon Keyes, ID: 100897196
- Bernard Llanos, ID: 100793648

## Building and Operating Instructions

This project will build and run in the COMP3004A virtual machine
(Ubuntu 12.04 LTS, 32-bit).

Note that the build steps must be repeated on each host
on which the server and client processes are to be run.

Steps 3 and 4 (networking configuration) can be skipped if all client processes
are running on the same virtual machine as the server.

1. Open `COMP3004A_project_teaQup.pro` with Qt Creator.
   1. If this is the first time that the project has been opened with Qt Creator,
      Qt Creator will provide a configuration screen.
      Qt Creator's automatic project configuration should not need to be adjusted;
      Simply navigate to the 'Edit' mode of the IDE by clicking "Configure Project".
   2. Note that development was carried out using Qt 5.0.2. Please change the 'Desktop' kit
      to use this version of Qt.
2. Build the appropriate project on each host (`client` or `server`) using Qt Creator.
3. Server network configuration
   1. Start the server process by choosing to run the `server` project.
   2. Terminate the server process (e.g. using `CTRL+C`).
   3. Navigate to the build folder for the server process
      (something like `../build-cuTPS_D4_teaQup-Desktop-Debug/server` relative
       to the `.pro` project file) and open `ServerConfigFile.txt`.
   4. Run the command `ifconfig` in the virtual machine.
   5. Replace the number next to `SERVER_IP_ADDRESS` in `ServerConfigFile.txt` with the IP
      address assigned to `eth2` in the output of `ifconfig`.
4. Client network configuration
   1. Start the client process by choosing to run the `client` project.
   2. Terminate the clinet process by closing its window.
   3. Navigate to the build folder for the client process
      (something like `../build-cuTPS_D4_teaQup-Desktop-Debug/client` relative
       to the `.pro` project file) and open `ServerConfigFile.txt`.
   4. Run the command `ipconfig` in the Windows host (or run the equivalent command in your
      host environment) of the *server*'s virtual machine.
   5. Replace the number next to `SERVER_IP_ADDRESS` in `ServerConfigFile.txt` with the IP
      address of the host determined in step 4.
5. Start the server process by choosing to run the `server` project.
6. Start the client process(es) by choosing to run the `client` project.
7. Logging-in on the client.
   - Use 100845934 or 100945234 to log in as either of the two student users.
   - Use 100945932 to log in as a content manager.
   - Note: Users can be logged into on more than one machine at a time.

## Sample Data

The system's database will be created and populated with sample data when first run. The script
used to set up the database is `cuTPS.sql`.

Note, however, that the book list shown to student users is hardcoded, rather than
retrieved from the database. The book list shown to content managers originates from the database.

All messages received from client processes, as well as operations on the database, are logged
to the terminal in which the server process is running.

## Code References and Acknowledgements

None currently, outside of Qt documentation and tutorials.

Websites consulted for ideas:

#### Serialization
- http://www.ics.com/blog/object-serialization-and-persistence-using-qdatastream#.VFtkPSUjthE
- http://www.mimec.org/node/351
