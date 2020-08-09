#include <math.h>

#include <fstream>
#include <iostream>

extern "C" {
#include <raylib.h>
}

#include <networktables/NetworkTableInstance.h>

#include "cxxopts.hpp"
#include "json.hpp"

// Screen sizing
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// NT instance
nt::NetworkTableInstance ntInst;

Vector3 fetchRobotPose() {
    // Get pose info
    float x = (float)ntInst.GetEntry("drivetrain_x").GetDouble(0.0);
    float y = (float)ntInst.GetEntry("drivetrain_y").GetDouble(0.0);

    return (Vector3){x, 0.0f, y};
}
Vector3 fetchRobotNormal(Vector3 pose, float radius) {
    // Get heading
    float degrees = (float)ntInst.GetEntry("drivetrain_theta").GetDouble(0.0);
    float x = std::cos(DEG2RAD * degrees);
    float y = std::sin(DEG2RAD * degrees);

    Vector3 unit = (Vector3){x, 0.0f, y};

    return (Vector3){pose.x + unit.x * radius, pose.y + unit.y * radius,
                     pose.z + unit.z * radius};
}

int main(int argc, char** argv) {
    // Handle argument parsing
    cxxopts::Options options(
        "FRCWorld", "A tool for visualizing an FRC robot's pose in real time");
    options.add_options()("i,ip", "Robot IP address",
                          cxxopts::value<std::string>())(
        "c,config", "Config JSON file", cxxopts::value<std::string>())(
        "h,help", "Print usage");
    auto args = options.parse(argc, argv);

    // Ensure required options exist
    if (!args.count("config") || !args.count("ip") || args.count("help")) {
        std::cout << options.help() << std::endl;
        return 1;
    }

    // Get config file
    std::ifstream f;
    f.open(args["config"].as<std::string>());

    // Check to make sure the config file exists
    if (f.fail()) {
        std::cout << "Invalid config file" << std::endl;
        return 1;
    }

    // Load all configuration data
    nlohmann::json j;
    f >> j;

    // Get all needed config fields
    float robotWidth = j["robot"]["width"].get<float>();
    float robotLength = j["robot"]["length"].get<float>();
    float robotHeight = j["robot"]["height"].get<float>();

    float fieldWidth = j["field"]["width"].get<float>();
    float fieldLength = j["field"]["length"].get<float>();
    float fieldHeight = 0.25f;

    // Define a robot pose and field pose
    Vector3 robotPose = {0.0f, 0.0f, 0.0f};
    float robotRadius = std::max(robotWidth, robotLength) / 2;
    Vector3 robotNormal = (Vector3){0.0f, 0.0f, 1.0f};
    Vector3 fieldPose = {0.0f, ((robotHeight / 2) * -1) - fieldHeight / 2,
                         (fieldLength / 2) - (robotLength / 2)};

    // Make a networktables connection
    ntInst = nt::NetworkTableInstance::Create();
    ntInst.StartClient(args["ip"].as<std::string>().c_str());
    ntInst.SetUpdateRate(0.01);

    // Init a raylib window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "FRCWorld 3D Robot viewer");

    // Define a 3D camera
    Camera3D camera = {0};
    camera.position = (Vector3){10.0f, 10.0f, 10.0f};  // Camera position
    camera.target = fieldPose;  // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f,
                          0.0f};  // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;          // Camera field-of-view Y
    camera.type = CAMERA_PERSPECTIVE;  // Camera mode type

    // Enable freecam
    SetCameraMode(camera, CAMERA_FREE);

    // Set the window FPS cap
    SetTargetFPS(60);

    // Render loop
    while (!WindowShouldClose()) {
        // Get a new position for the robot
        robotPose = fetchRobotPose();
        robotNormal = fetchRobotNormal(robotPose, robotRadius);

        // Update the camera
        UpdateCamera(&camera);

        // Render routine
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        // Render the robot (TODO)
        // DrawCube(robotPose, robotWidth, robotHeight, robotLength, RED);
        // DrawCubeWires(robotPose, robotWidth, robotHeight, robotLength, GRAY);
        DrawSphere(robotPose, robotRadius, RED);
        DrawSphereWires(robotPose, robotRadius, 5, 10, MAROON);
        DrawSphere(robotNormal, 0.1, BLUE);
        DrawSphereWires(robotNormal, 0.1, 3, 5, WHITE);

        // Render the "floor"
        DrawCube(fieldPose, fieldWidth, fieldHeight, fieldLength, LIGHTGRAY);
        DrawCubeWires(fieldPose, fieldWidth, fieldHeight, fieldLength, GRAY);

        EndMode3D();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
