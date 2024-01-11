/*
#include <iostream>

#include "turbine.h"

class TurbineSpeedControlSystemTester {
public:
    static void runTests() {
        try {
            TurbineSpeedControlSystem controlSystem;
            char choice;

            do {
                std::cout << "\n\t\tTurbineSpeedControlSystem Tester\n";
                std::cout << "1. Simulate System Operation\n";
                std::cout << "2. Display Sensor Status\n";
                std::cout << "3. Quit\n";
                std::cout << "Enter choice (1-3): ";
                std::cin >> choice;

                switch (choice) {
                    case '1':
                        // Simulate system operation
                        simulateSystemOperation(controlSystem);
                        break;
                    case '2':
                        // Display sensor status
                        displaySensorStatus(controlSystem);
                        break;
                    case '3':
                        // Quit the tester
                        break;
                    default:
                        std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
                }
            } while (choice != '3');
        } catch (...) {
            std::cout << "Error initializing TurbineSpeedControlSystem.\n";
        }
    }

private:
    static void simulateSystemOperation(TurbineSpeedControlSystem& controlSystem) {
        for (int i = 0; i < 180; i++) {
            float rpmIncrease = std::min(50.0f, (TurbineSpeedControlSystem::targetRPM - controlSystem.rpmSensor.rpmReading) * 0.05f);
            float simulatedRPM = controlSystem.rpmSensor.rpmReading + rpmIncrease;
            controlSystem.rpmSensor.measureRPM(simulatedRPM);
            controlSystem.updateSensorStatus();

            if (controlSystem.isSystemOperational()) {
                controlSystem.compareRPM();

                std::cout << "System is operational. Time: " << i << "s, "
                          << "Current RPM: " << controlSystem.currentRPM << ", "
                          << "Valve Position: " << controlSystem.valvePosition * 100 << "%"
                          << std::endl;
            } else {
                std::cout << "Sensor failure detected. System is not operational." << std::endl;
                break; // Exit the loop if the system is not operational
            }
        }
    }

    static void displaySensorStatus(const TurbineSpeedControlSystem& controlSystem) {
        std::cout << "\nSensor Status:\n";
        std::cout << "RPM Sensor: " << (controlSystem.rpmSensor.sensorStatus ? "Operational" : "Not Operational") << std::endl;
        std::cout << "Valve Position Sensor: " << (controlSystem.valveSensor.sensorStatus ? "Operational" : "Not Operational") << std::endl;
    }
};

int main() {
    TurbineSpeedControlSystemTester::runTests();
    return 0;
}

*/