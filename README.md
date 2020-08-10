# FRCWorld ![Bazel Build](https://github.com/Ewpratten/frcworld/workflows/Bazel%20Build/badge.svg)
A tool for visualizing an FRC robot's pose in real time.

This is an experimental project of mine, and the first "real" 3D application I have built (aside from raytracing).

## Building 

This project uses the [Bazel buildsystem](https://bazel.build). To build and run the application, run the following:

```sh
# Build the binary
bazel build //frcworld

# Run with default settings
./bazel-bin/frcworld/frcworld -i 10.TE.AM.2 -c ./examples/config.json
```

Replace `TE` and `AM` with your team number, and feel free to edit the config JSON file with your robot's measurements.

## Sending data from a robot

This program requires the attached robot to be publishing the following NetworkTables entries as type `double`.

```sh
/drivetrain_x       # X position in meters
/drivetrain_y       # Y position in meters
/drivetrain_theta   # Heading in degrees
```

## Project dependancies

This project is built on the following technology:
 - [raylib](https://www.raylib.com)
 - [ntcore](https://first.wpi.edu/FRC/roborio/release/docs/cpp/group__ntcore__cpp__api.html)

Some [clever trickery](https://github.com/Ewpratten/frcworld/blob/master/thirdparty/ntcore/BUILD) was required to strip down the [allwpilib](https://github.com/wpilibsuite/allwpilib/) monolith and only build what is needed from the project. Despite my work to build only the needed libraries, the ntcore compile time is still around 2 minutes locally, and 6 minutes in the CI pipeline.

## Screenshots

![example field](assets/frcworldv1.png)

*The example field and "robot"*